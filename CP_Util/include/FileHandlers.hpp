// https://oroboro.com/file-handle-leaks-server/ 

#pragma once
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>     
#include <Logger.hpp>

namespace lte
{
namespace common
{
void showFDInfo( const auto& fd )
{
   char buf[256];
 
   auto fd_flags = fcntl( fd, F_GETFD ); 
   if ( fd_flags == -1 ) return;
 
   auto fl_flags = fcntl( fd, F_GETFL ); 
   if ( fl_flags == -1 ) return;
 
   char path[256];
   sprintf( path, "/proc/self/fd/%d", fd );
 
   memset( &buf[0], 0, 256 );
   ssize_t s = readlink( path, &buf[0], 256 );
   if ( s == -1 )
   {
        dbg()<< " (" << path << "): " << "not available";
        return;
   }
   
   std::unique_ptr<std::stringstream> stream = std::make_unique<std::stringstream>();
   *stream << fd << " (" << buf << "): ";
 
   if ( fd_flags & FD_CLOEXEC )  *stream << "cloexec ";
 
   // file status
   if ( fl_flags & O_APPEND   )  *stream << "append ";
   if ( fl_flags & O_NONBLOCK )  *stream << "nonblock ";
 
   // acc mode
   if ( fl_flags & O_RDONLY   )  *stream << "read-only ";
   if ( fl_flags & O_RDWR     )  *stream << "read-write ";
   if ( fl_flags & O_WRONLY   )  *stream << "write-only ";
 
   if ( fl_flags & O_DSYNC    )  *stream << "dsync ";
   if ( fl_flags & O_RSYNC    )  *stream << "rsync ";
   if ( fl_flags & O_SYNC     )  *stream << "sync ";
 
   struct flock fl;
   fl.l_type = F_WRLCK;
   fl.l_whence = 0;
   fl.l_start = 0;
   fl.l_len = 0;
   fcntl( fd, F_GETLK, &fl );
   if ( fl.l_type != F_UNLCK )
   {
      if ( fl.l_type == F_WRLCK )
      {
        *stream << "write-locked";
      }
      else
      {
         *stream << "read-locked";
      }
      *stream << "(pid:" << fl.l_pid << ") ";
   }
   
   dbg() << stream->str();
}

void showFDInfo()
{
   const auto numHandles = getdtablesize();
 
   for ( auto i = 0; i < numHandles; i++ )
   {
      auto fd_flags = fcntl( i, F_GETFD ); 
      if ( fd_flags == -1 ) continue;
 
      showFDInfo( i );
   }
}
}
}