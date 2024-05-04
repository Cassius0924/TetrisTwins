// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: room.proto
// Protobuf C++ Version: 5.26.1

#include "proto/room.pb.h"

#include <algorithm>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"
#include "google/protobuf/generated_message_tctable_impl.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::google::protobuf;
namespace _pbi = ::google::protobuf::internal;
namespace _fl = ::google::protobuf::internal::field_layout;
namespace proto {

inline constexpr RoomMessage::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : ip_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        name_(
            &::google::protobuf::internal::fixed_address_empty_string,
            ::_pbi::ConstantInitialized()),
        id_{0},
        port_{0},
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR RoomMessage::RoomMessage(::_pbi::ConstantInitialized)
    : _impl_(::_pbi::ConstantInitialized()) {}
struct RoomMessageDefaultTypeInternal {
  PROTOBUF_CONSTEXPR RoomMessageDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~RoomMessageDefaultTypeInternal() {}
  union {
    RoomMessage _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 RoomMessageDefaultTypeInternal _RoomMessage_default_instance_;
}  // namespace proto
static ::_pb::Metadata file_level_metadata_room_2eproto[1];
static constexpr const ::_pb::EnumDescriptor**
    file_level_enum_descriptors_room_2eproto = nullptr;
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_room_2eproto = nullptr;
const ::uint32_t
    TableStruct_room_2eproto::offsets[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
        protodesc_cold) = {
        ~0u,  // no _has_bits_
        PROTOBUF_FIELD_OFFSET(::proto::RoomMessage, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::proto::RoomMessage, _impl_.id_),
        PROTOBUF_FIELD_OFFSET(::proto::RoomMessage, _impl_.ip_),
        PROTOBUF_FIELD_OFFSET(::proto::RoomMessage, _impl_.port_),
        PROTOBUF_FIELD_OFFSET(::proto::RoomMessage, _impl_.name_),
};

static const ::_pbi::MigrationSchema
    schemas[] ABSL_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
        {0, -1, -1, sizeof(::proto::RoomMessage)},
};
static const ::_pb::Message* const file_default_instances[] = {
    &::proto::_RoomMessage_default_instance_._instance,
};
const char descriptor_table_protodef_room_2eproto[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
    protodesc_cold) = {
    "\n\nroom.proto\022\005proto\"A\n\013RoomMessage\022\n\n\002id"
    "\030\001 \001(\005\022\n\n\002ip\030\002 \001(\t\022\014\n\004port\030\003 \001(\005\022\014\n\004name"
    "\030\004 \001(\tb\006proto3"
};
static ::absl::once_flag descriptor_table_room_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_room_2eproto = {
    false,
    false,
    94,
    descriptor_table_protodef_room_2eproto,
    "room.proto",
    &descriptor_table_room_2eproto_once,
    nullptr,
    0,
    1,
    schemas,
    file_default_instances,
    TableStruct_room_2eproto::offsets,
    file_level_metadata_room_2eproto,
    file_level_enum_descriptors_room_2eproto,
    file_level_service_descriptors_room_2eproto,
};

// This function exists to be marked as weak.
// It can significantly speed up compilation by breaking up LLVM's SCC
// in the .pb.cc translation units. Large translation units see a
// reduction of more than 35% of walltime for optimized builds. Without
// the weak attribute all the messages in the file, including all the
// vtables and everything they use become part of the same SCC through
// a cycle like:
// GetMetadata -> descriptor table -> default instances ->
//   vtables -> GetMetadata
// By adding a weak function here we break the connection from the
// individual vtables back into the descriptor table.
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_room_2eproto_getter() {
  return &descriptor_table_room_2eproto;
}
namespace proto {
// ===================================================================

class RoomMessage::_Internal {
 public:
};

RoomMessage::RoomMessage(::google::protobuf::Arena* arena)
    : ::google::protobuf::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:proto.RoomMessage)
}
inline PROTOBUF_NDEBUG_INLINE RoomMessage::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from)
      : ip_(arena, from.ip_),
        name_(arena, from.name_),
        _cached_size_{0} {}

RoomMessage::RoomMessage(
    ::google::protobuf::Arena* arena,
    const RoomMessage& from)
    : ::google::protobuf::Message(arena) {
  RoomMessage* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_);
  ::memcpy(reinterpret_cast<char *>(&_impl_) +
               offsetof(Impl_, id_),
           reinterpret_cast<const char *>(&from._impl_) +
               offsetof(Impl_, id_),
           offsetof(Impl_, port_) -
               offsetof(Impl_, id_) +
               sizeof(Impl_::port_));

  // @@protoc_insertion_point(copy_constructor:proto.RoomMessage)
}
inline PROTOBUF_NDEBUG_INLINE RoomMessage::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : ip_(arena),
        name_(arena),
        _cached_size_{0} {}

inline void RoomMessage::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  ::memset(reinterpret_cast<char *>(&_impl_) +
               offsetof(Impl_, id_),
           0,
           offsetof(Impl_, port_) -
               offsetof(Impl_, id_) +
               sizeof(Impl_::port_));
}
RoomMessage::~RoomMessage() {
  // @@protoc_insertion_point(destructor:proto.RoomMessage)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void RoomMessage::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  _impl_.ip_.Destroy();
  _impl_.name_.Destroy();
  _impl_.~Impl_();
}

const ::google::protobuf::MessageLite::ClassData*
RoomMessage::GetClassData() const {
  PROTOBUF_CONSTINIT static const ::google::protobuf::MessageLite::
      ClassDataFull _data_ = {
          {
              nullptr,  // OnDemandRegisterArenaDtor
              PROTOBUF_FIELD_OFFSET(RoomMessage, _impl_._cached_size_),
              false,
          },
          &RoomMessage::MergeImpl,
          &RoomMessage::kDescriptorMethods,
      };
  return &_data_;
}
PROTOBUF_NOINLINE void RoomMessage::Clear() {
// @@protoc_insertion_point(message_clear_start:proto.RoomMessage)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.ip_.ClearToEmpty();
  _impl_.name_.ClearToEmpty();
  ::memset(&_impl_.id_, 0, static_cast<::size_t>(
      reinterpret_cast<char*>(&_impl_.port_) -
      reinterpret_cast<char*>(&_impl_.id_)) + sizeof(_impl_.port_));
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

const char* RoomMessage::_InternalParse(
    const char* ptr, ::_pbi::ParseContext* ctx) {
  ptr = ::_pbi::TcParser::ParseLoop(this, ptr, ctx, &_table_.header);
  return ptr;
}


PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<2, 4, 0, 32, 2> RoomMessage::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    4, 24,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967280,  // skipmap
    offsetof(decltype(_table_), field_entries),
    4,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    &_RoomMessage_default_instance_._instance,
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::proto::RoomMessage>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    // string name = 4;
    {::_pbi::TcParser::FastUS1,
     {34, 63, 0, PROTOBUF_FIELD_OFFSET(RoomMessage, _impl_.name_)}},
    // int32 id = 1;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint32_t, offsetof(RoomMessage, _impl_.id_), 63>(),
     {8, 63, 0, PROTOBUF_FIELD_OFFSET(RoomMessage, _impl_.id_)}},
    // string ip = 2;
    {::_pbi::TcParser::FastUS1,
     {18, 63, 0, PROTOBUF_FIELD_OFFSET(RoomMessage, _impl_.ip_)}},
    // int32 port = 3;
    {::_pbi::TcParser::SingularVarintNoZag1<::uint32_t, offsetof(RoomMessage, _impl_.port_), 63>(),
     {24, 63, 0, PROTOBUF_FIELD_OFFSET(RoomMessage, _impl_.port_)}},
  }}, {{
    65535, 65535
  }}, {{
    // int32 id = 1;
    {PROTOBUF_FIELD_OFFSET(RoomMessage, _impl_.id_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kInt32)},
    // string ip = 2;
    {PROTOBUF_FIELD_OFFSET(RoomMessage, _impl_.ip_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
    // int32 port = 3;
    {PROTOBUF_FIELD_OFFSET(RoomMessage, _impl_.port_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kInt32)},
    // string name = 4;
    {PROTOBUF_FIELD_OFFSET(RoomMessage, _impl_.name_), 0, 0,
    (0 | ::_fl::kFcSingular | ::_fl::kUtf8String | ::_fl::kRepAString)},
  }},
  // no aux_entries
  {{
    "\21\0\2\0\4\0\0\0"
    "proto.RoomMessage"
    "ip"
    "name"
  }},
};

::uint8_t* RoomMessage::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:proto.RoomMessage)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  // int32 id = 1;
  if (this->_internal_id() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::
        WriteInt32ToArrayWithField<1>(
            stream, this->_internal_id(), target);
  }

  // string ip = 2;
  if (!this->_internal_ip().empty()) {
    const std::string& _s = this->_internal_ip();
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "proto.RoomMessage.ip");
    target = stream->WriteStringMaybeAliased(2, _s, target);
  }

  // int32 port = 3;
  if (this->_internal_port() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::
        WriteInt32ToArrayWithField<3>(
            stream, this->_internal_port(), target);
  }

  // string name = 4;
  if (!this->_internal_name().empty()) {
    const std::string& _s = this->_internal_name();
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::google::protobuf::internal::WireFormatLite::SERIALIZE, "proto.RoomMessage.name");
    target = stream->WriteStringMaybeAliased(4, _s, target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target =
        ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
            _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:proto.RoomMessage)
  return target;
}

::size_t RoomMessage::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:proto.RoomMessage)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string ip = 2;
  if (!this->_internal_ip().empty()) {
    total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                    this->_internal_ip());
  }

  // string name = 4;
  if (!this->_internal_name().empty()) {
    total_size += 1 + ::google::protobuf::internal::WireFormatLite::StringSize(
                                    this->_internal_name());
  }

  // int32 id = 1;
  if (this->_internal_id() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(
        this->_internal_id());
  }

  // int32 port = 3;
  if (this->_internal_port() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(
        this->_internal_port());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}


void RoomMessage::MergeImpl(::google::protobuf::MessageLite& to_msg, const ::google::protobuf::MessageLite& from_msg) {
  auto* const _this = static_cast<RoomMessage*>(&to_msg);
  auto& from = static_cast<const RoomMessage&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:proto.RoomMessage)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_ip().empty()) {
    _this->_internal_set_ip(from._internal_ip());
  }
  if (!from._internal_name().empty()) {
    _this->_internal_set_name(from._internal_name());
  }
  if (from._internal_id() != 0) {
    _this->_impl_.id_ = from._impl_.id_;
  }
  if (from._internal_port() != 0) {
    _this->_impl_.port_ = from._impl_.port_;
  }
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void RoomMessage::CopyFrom(const RoomMessage& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:proto.RoomMessage)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

PROTOBUF_NOINLINE bool RoomMessage::IsInitialized() const {
  return true;
}

void RoomMessage::InternalSwap(RoomMessage* PROTOBUF_RESTRICT other) {
  using std::swap;
  auto* arena = GetArena();
  ABSL_DCHECK_EQ(arena, other->GetArena());
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.ip_, &other->_impl_.ip_, arena);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.name_, &other->_impl_.name_, arena);
  ::google::protobuf::internal::memswap<
      PROTOBUF_FIELD_OFFSET(RoomMessage, _impl_.port_)
      + sizeof(RoomMessage::_impl_.port_)
      - PROTOBUF_FIELD_OFFSET(RoomMessage, _impl_.id_)>(
          reinterpret_cast<char*>(&_impl_.id_),
          reinterpret_cast<char*>(&other->_impl_.id_));
}

::google::protobuf::Metadata RoomMessage::GetMetadata() const {
  return ::_pbi::AssignDescriptors(&descriptor_table_room_2eproto_getter,
                                   &descriptor_table_room_2eproto_once,
                                   file_level_metadata_room_2eproto[0]);
}
// @@protoc_insertion_point(namespace_scope)
}  // namespace proto
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google
// @@protoc_insertion_point(global_scope)
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2
static ::std::false_type _static_init_ PROTOBUF_UNUSED =
    (::_pbi::AddDescriptors(&descriptor_table_room_2eproto),
     ::std::false_type{});
#include "google/protobuf/port_undef.inc"