#pragma once

#if defined(__GNUC__) || defined(__clang__)
#define H5_DEPRECATED(msg) __attribute__((deprecated(#msg)))
#elif defined(_MSC_VER)
#define H5_DEPRECATED(msg) __declspec(deprecated(#msg))
#else
#pragma message("WARNING: Compiler doesn't support deprecation")
#define H5_DEPRECATED(msg)
#endif

#if defined(__GNUC__) || defined(__clang__)
#define H5_DEPRECATED_USING(msg) H5_DEPRECATED((msg))
#else
#pragma message("WARNING: Compiler doesn't support deprecating using statements.")
#define H5_DEPRECATED_USING(msg)
#endif

#if defined(HIGHFIVE_USE_RESTVOL)
#define HIGHFIVE_NOEXCEPT_IF_NOT_RESTVOL
#else
#define HIGHFIVE_NOEXCEPT_IF_NOT_RESTVOL noexcept
#endif

// Forward declarations

namespace HighFive {

enum class LinkType;
enum class ObjectType;
enum class PropertyType;

class Attribute;
class DataSet;
class DataSpace;
class DataType;
class Exception;
class File;
class FileDriver;
class Group;
class Object;
class ObjectInfo;
class Reference;
class Selection;
class SilenceHDF5;

template <typename T>
class AtomicType;

template <typename Derivate>
class AnnotateTraits;

template <typename Derivate>
class NodeTraits;

template <PropertyType T>
class PropertyList;

}  // namespace HighFive
