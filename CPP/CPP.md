# LambdaExpression

# RAII
Resource Acquisition is Initialzation (RAII) is a C++ programming technique which binds that life cycle of a resource that must be aquire before use (allocated heap memory, thread of execuation, open socket, open file, locked mutex, disk space, db connection) to the lifetime of an object.

RAII summarized:

1. encapsulate each resource into a class, where
* the constructor acquires the resource and establishes all class invariants or throws an exception if that cannot be done,
* the destructor releases the resource and never throws exceptions;

2. always use the resource via an instance of a RAII-class that either
* has automatic storage duration or temporary lifetime itself, or
* has lifetime that is bounded by the lifetime of an automatic or temporary object

The C++ library classes that manage their own resources follow RAII: std::string, std::vector, std::jthread (since C++20), and many others acquire their resources in constructors (which throw exceptions on errors), release them in their destructors (which never throw), and don't require explicit cleanup.