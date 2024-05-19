// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: signal.proto
// Protobuf C++ Version: 5.26.1

#ifndef GOOGLE_PROTOBUF_INCLUDED_signal_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_signal_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>
#include <utility>

#include "google/protobuf/port_def.inc"
#if PROTOBUF_VERSION != 5026001
#error "Protobuf C++ gencode is built with an incompatible version of"
#error "Protobuf C++ headers/runtime. See"
#error "https://protobuf.dev/support/cross-version-runtime-guarantee/#cpp"
#endif
#include "google/protobuf/port_undef.inc"
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_tctable_decl.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/generated_enum_reflection.h"
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_signal_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_signal_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_signal_2eproto;
namespace proto {
class SignalMessage;
struct SignalMessageDefaultTypeInternal;
extern SignalMessageDefaultTypeInternal _SignalMessage_default_instance_;
}  // namespace proto
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace proto {
enum Signal : int {
  START = 0,
  QUIT = 1,
  Signal_INT_MIN_SENTINEL_DO_NOT_USE_ =
      std::numeric_limits<::int32_t>::min(),
  Signal_INT_MAX_SENTINEL_DO_NOT_USE_ =
      std::numeric_limits<::int32_t>::max(),
};

bool Signal_IsValid(int value);
extern const uint32_t Signal_internal_data_[];
constexpr Signal Signal_MIN = static_cast<Signal>(0);
constexpr Signal Signal_MAX = static_cast<Signal>(1);
constexpr int Signal_ARRAYSIZE = 1 + 1;
const ::google::protobuf::EnumDescriptor*
Signal_descriptor();
template <typename T>
const std::string& Signal_Name(T value) {
  static_assert(std::is_same<T, Signal>::value ||
                    std::is_integral<T>::value,
                "Incorrect type passed to Signal_Name().");
  return Signal_Name(static_cast<Signal>(value));
}
template <>
inline const std::string& Signal_Name(Signal value) {
  return ::google::protobuf::internal::NameOfDenseEnum<Signal_descriptor,
                                                 0, 1>(
      static_cast<int>(value));
}
inline bool Signal_Parse(absl::string_view name, Signal* value) {
  return ::google::protobuf::internal::ParseNamedEnum<Signal>(
      Signal_descriptor(), name, value);
}

// ===================================================================


// -------------------------------------------------------------------

class SignalMessage final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:proto.SignalMessage) */ {
 public:
  inline SignalMessage() : SignalMessage(nullptr) {}
  ~SignalMessage() override;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR SignalMessage(
      ::google::protobuf::internal::ConstantInitialized);

  inline SignalMessage(const SignalMessage& from) : SignalMessage(nullptr, from) {}
  inline SignalMessage(SignalMessage&& from) noexcept
      : SignalMessage(nullptr, std::move(from)) {}
  inline SignalMessage& operator=(const SignalMessage& from) {
    CopyFrom(from);
    return *this;
  }
  inline SignalMessage& operator=(SignalMessage&& from) noexcept {
    if (this == &from) return *this;
    if (GetArena() == from.GetArena()
#ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetArena() != nullptr
#endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const SignalMessage& default_instance() {
    return *internal_default_instance();
  }
  static inline const SignalMessage* internal_default_instance() {
    return reinterpret_cast<const SignalMessage*>(
        &_SignalMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 0;
  friend void swap(SignalMessage& a, SignalMessage& b) { a.Swap(&b); }
  inline void Swap(SignalMessage* other) {
    if (other == this) return;
#ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() != nullptr && GetArena() == other->GetArena()) {
#else   // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() == other->GetArena()) {
#endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(SignalMessage* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  SignalMessage* New(::google::protobuf::Arena* arena = nullptr) const final {
    return ::google::protobuf::Message::DefaultConstruct<SignalMessage>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const SignalMessage& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const SignalMessage& from) { SignalMessage::MergeImpl(*this, from); }

  private:
  static void MergeImpl(
      ::google::protobuf::MessageLite& to_msg,
      const ::google::protobuf::MessageLite& from_msg);

  public:
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::google::protobuf::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void InternalSwap(SignalMessage* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "proto.SignalMessage"; }

 protected:
  explicit SignalMessage(::google::protobuf::Arena* arena);
  SignalMessage(::google::protobuf::Arena* arena, const SignalMessage& from);
  SignalMessage(::google::protobuf::Arena* arena, SignalMessage&& from) noexcept
      : SignalMessage(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::MessageLite::ClassData* GetClassData()
      const final;

 public:
  ::google::protobuf::Metadata GetMetadata() const final;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kSignalFieldNumber = 1,
  };
  // .proto.Signal signal = 1;
  void clear_signal() ;
  ::proto::Signal signal() const;
  void set_signal(::proto::Signal value);

  private:
  ::proto::Signal _internal_signal() const;
  void _internal_set_signal(::proto::Signal value);

  public:
  // @@protoc_insertion_point(class_scope:proto.SignalMessage)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      0, 1, 0,
      0, 2>
      _table_;
  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from);
    int signal_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_signal_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// SignalMessage

// .proto.Signal signal = 1;
inline void SignalMessage::clear_signal() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.signal_ = 0;
}
inline ::proto::Signal SignalMessage::signal() const {
  // @@protoc_insertion_point(field_get:proto.SignalMessage.signal)
  return _internal_signal();
}
inline void SignalMessage::set_signal(::proto::Signal value) {
  _internal_set_signal(value);
  // @@protoc_insertion_point(field_set:proto.SignalMessage.signal)
}
inline ::proto::Signal SignalMessage::_internal_signal() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return static_cast<::proto::Signal>(_impl_.signal_);
}
inline void SignalMessage::_internal_set_signal(::proto::Signal value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.signal_ = value;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace proto


namespace google {
namespace protobuf {

template <>
struct is_proto_enum<::proto::Signal> : std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor<::proto::Signal>() {
  return ::proto::Signal_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_signal_2eproto_2epb_2eh
