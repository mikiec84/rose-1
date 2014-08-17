#ifndef BACKSTROKE_RUNTIMESYSTEM
#define BACKSTROKE_RUNTIMESYSTEM

#include <stack>
#include <queue>
#include <deque>
#include <inttypes.h>

using namespace std;

namespace Backstroke {

#include "runtime_macros.h"

class RunTimeSystem {
 public:
  RunTimeSystem();
  typedef void* ptr;
  void initializeForwardEvent();
  void finalizeForwardEvent();
  void reverseEvent();
  void commitEvent();
  void registerForCommit(ptr p);

  size_t numberOfUncommittedEvents();
  size_t size();
  size_t currentEventLength();

  // headers with private data members for all built-in types
  STACK_ASSIGN_RESTORE_HEADER(bool,bool);
  STACK_ASSIGN_RESTORE_HEADER(char,char);
  STACK_ASSIGN_RESTORE_HEADER(short int,shortint);
  STACK_ASSIGN_RESTORE_HEADER(int,int);
  STACK_ASSIGN_RESTORE_HEADER(long int,longint);
  STACK_ASSIGN_RESTORE_HEADER(long long int,longlongint);
  STACK_ASSIGN_RESTORE_HEADER(unsigned short int,ushortint);
  STACK_ASSIGN_RESTORE_HEADER(unsigned int,uint);
  STACK_ASSIGN_RESTORE_HEADER(unsigned long int,ulongint);
  STACK_ASSIGN_RESTORE_HEADER(unsigned long long int,ulonglongint);
  STACK_ASSIGN_RESTORE_HEADER(float,float);
  STACK_ASSIGN_RESTORE_HEADER(double,double);
  STACK_ASSIGN_RESTORE_HEADER(long double,longdouble);

  // headers for ptr handling
 private:
  stack<pair<ptr*, ptr> > stack_ptr;
  void restore_ptr();
 public:
  ptr assignptr(ptr* address, ptr value);
  ptr* avpushptr(ptr* address);

 public:
  void init_stack_info(); // must be called to initialize run-time-system
  void print_stack_info();
  bool is_stack_ptr(void *ptr);

 private:
  enum BuiltInType {
    BITYPE_BOOL,
    BITYPE_CHAR,
    BITYPE_SHORT_INT,
    BITYPE_INT,
    BITYPE_LONG_INT,
    BITYPE_LONG_LONG_INT,
    BITYPE_USHORT_INT,
    BITYPE_UINT,
    BITYPE_ULONG_INT,
    BITYPE_ULONG_LONG_INT,
    BITYPE_FLOAT,
    BITYPE_DOUBLE,
    BITYPE_LONG_DOUBLE,
    BITYPE_PTR,
    BITYPE_NUM
  };
  void restore(BuiltInType bitype);
  struct EventRecord {
    void deallocateHeapQueue();
    stack<BuiltInType> stack_bitype;
    queue<ptr> registeredHeapQueue;
  };
  deque<EventRecord*> eventRecordDeque;
  size_t typeSize(BuiltInType biType);
  EventRecord* currentEventRecord;

  // STACK/HEAP detection
  uintptr_t prog_stack_bottom;
  uintptr_t prog_stack_local; // can be set to function stack (default: same as stack_bottom)
  uintptr_t prog_stack_max;
};

}
#endif
