# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: messages.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='messages.proto',
  package='lte',
  serialized_pb=_b('\n\x0emessages.proto\x12\x03lte\"\x17\n\tAttachReq\x12\n\n\x02id\x18\x01 \x02(\x05\"\x18\n\nAttachResp\x12\n\n\x02id\x18\x01 \x02(\x05\"\x17\n\tDetachReq\x12\n\n\x02id\x18\x01 \x02(\x05\"[\n\nDetachResp\x12\n\n\x02id\x18\x01 \x02(\x05\x12&\n\x06status\x18\x02 \x02(\x0e\x32\x16.lte.DetachResp.Status\"\x19\n\x06Status\x12\x06\n\x02OK\x10\x00\x12\x07\n\x03NOK\x10\x01\"\xc4\x01\n\x0eMessageWrapper\x12\x0f\n\x07version\x18\x01 \x02(\x05\x12$\n\nattach_req\x18\x02 \x01(\x0b\x32\x0e.lte.AttachReqH\x00\x12&\n\x0b\x61ttach_resp\x18\x03 \x01(\x0b\x32\x0f.lte.AttachRespH\x00\x12$\n\ndetach_req\x18\x04 \x01(\x0b\x32\x0e.lte.DetachReqH\x00\x12&\n\x0b\x64\x65tach_resp\x18\x05 \x01(\x0b\x32\x0f.lte.DetachRespH\x00\x42\x05\n\x03msg')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)



_DETACHRESP_STATUS = _descriptor.EnumDescriptor(
  name='Status',
  full_name='lte.DetachResp.Status',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='OK', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='NOK', index=1, number=1,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=165,
  serialized_end=190,
)
_sym_db.RegisterEnumDescriptor(_DETACHRESP_STATUS)


_ATTACHREQ = _descriptor.Descriptor(
  name='AttachReq',
  full_name='lte.AttachReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='lte.AttachReq.id', index=0,
      number=1, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=23,
  serialized_end=46,
)


_ATTACHRESP = _descriptor.Descriptor(
  name='AttachResp',
  full_name='lte.AttachResp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='lte.AttachResp.id', index=0,
      number=1, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=48,
  serialized_end=72,
)


_DETACHREQ = _descriptor.Descriptor(
  name='DetachReq',
  full_name='lte.DetachReq',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='lte.DetachReq.id', index=0,
      number=1, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=74,
  serialized_end=97,
)


_DETACHRESP = _descriptor.Descriptor(
  name='DetachResp',
  full_name='lte.DetachResp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='id', full_name='lte.DetachResp.id', index=0,
      number=1, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='status', full_name='lte.DetachResp.status', index=1,
      number=2, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _DETACHRESP_STATUS,
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=99,
  serialized_end=190,
)


_MESSAGEWRAPPER = _descriptor.Descriptor(
  name='MessageWrapper',
  full_name='lte.MessageWrapper',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='version', full_name='lte.MessageWrapper.version', index=0,
      number=1, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='attach_req', full_name='lte.MessageWrapper.attach_req', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='attach_resp', full_name='lte.MessageWrapper.attach_resp', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='detach_req', full_name='lte.MessageWrapper.detach_req', index=3,
      number=4, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='detach_resp', full_name='lte.MessageWrapper.detach_resp', index=4,
      number=5, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
    _descriptor.OneofDescriptor(
      name='msg', full_name='lte.MessageWrapper.msg',
      index=0, containing_type=None, fields=[]),
  ],
  serialized_start=193,
  serialized_end=389,
)

_DETACHRESP.fields_by_name['status'].enum_type = _DETACHRESP_STATUS
_DETACHRESP_STATUS.containing_type = _DETACHRESP
_MESSAGEWRAPPER.fields_by_name['attach_req'].message_type = _ATTACHREQ
_MESSAGEWRAPPER.fields_by_name['attach_resp'].message_type = _ATTACHRESP
_MESSAGEWRAPPER.fields_by_name['detach_req'].message_type = _DETACHREQ
_MESSAGEWRAPPER.fields_by_name['detach_resp'].message_type = _DETACHRESP
_MESSAGEWRAPPER.oneofs_by_name['msg'].fields.append(
  _MESSAGEWRAPPER.fields_by_name['attach_req'])
_MESSAGEWRAPPER.fields_by_name['attach_req'].containing_oneof = _MESSAGEWRAPPER.oneofs_by_name['msg']
_MESSAGEWRAPPER.oneofs_by_name['msg'].fields.append(
  _MESSAGEWRAPPER.fields_by_name['attach_resp'])
_MESSAGEWRAPPER.fields_by_name['attach_resp'].containing_oneof = _MESSAGEWRAPPER.oneofs_by_name['msg']
_MESSAGEWRAPPER.oneofs_by_name['msg'].fields.append(
  _MESSAGEWRAPPER.fields_by_name['detach_req'])
_MESSAGEWRAPPER.fields_by_name['detach_req'].containing_oneof = _MESSAGEWRAPPER.oneofs_by_name['msg']
_MESSAGEWRAPPER.oneofs_by_name['msg'].fields.append(
  _MESSAGEWRAPPER.fields_by_name['detach_resp'])
_MESSAGEWRAPPER.fields_by_name['detach_resp'].containing_oneof = _MESSAGEWRAPPER.oneofs_by_name['msg']
DESCRIPTOR.message_types_by_name['AttachReq'] = _ATTACHREQ
DESCRIPTOR.message_types_by_name['AttachResp'] = _ATTACHRESP
DESCRIPTOR.message_types_by_name['DetachReq'] = _DETACHREQ
DESCRIPTOR.message_types_by_name['DetachResp'] = _DETACHRESP
DESCRIPTOR.message_types_by_name['MessageWrapper'] = _MESSAGEWRAPPER

AttachReq = _reflection.GeneratedProtocolMessageType('AttachReq', (_message.Message,), dict(
  DESCRIPTOR = _ATTACHREQ,
  __module__ = 'messages_pb2'
  # @@protoc_insertion_point(class_scope:lte.AttachReq)
  ))
_sym_db.RegisterMessage(AttachReq)

AttachResp = _reflection.GeneratedProtocolMessageType('AttachResp', (_message.Message,), dict(
  DESCRIPTOR = _ATTACHRESP,
  __module__ = 'messages_pb2'
  # @@protoc_insertion_point(class_scope:lte.AttachResp)
  ))
_sym_db.RegisterMessage(AttachResp)

DetachReq = _reflection.GeneratedProtocolMessageType('DetachReq', (_message.Message,), dict(
  DESCRIPTOR = _DETACHREQ,
  __module__ = 'messages_pb2'
  # @@protoc_insertion_point(class_scope:lte.DetachReq)
  ))
_sym_db.RegisterMessage(DetachReq)

DetachResp = _reflection.GeneratedProtocolMessageType('DetachResp', (_message.Message,), dict(
  DESCRIPTOR = _DETACHRESP,
  __module__ = 'messages_pb2'
  # @@protoc_insertion_point(class_scope:lte.DetachResp)
  ))
_sym_db.RegisterMessage(DetachResp)

MessageWrapper = _reflection.GeneratedProtocolMessageType('MessageWrapper', (_message.Message,), dict(
  DESCRIPTOR = _MESSAGEWRAPPER,
  __module__ = 'messages_pb2'
  # @@protoc_insertion_point(class_scope:lte.MessageWrapper)
  ))
_sym_db.RegisterMessage(MessageWrapper)


# @@protoc_insertion_point(module_scope)
