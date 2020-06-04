#include "il2cpp-config.h"

#if IL2CPP_SUPPORT_THREADS

#include "AtomicQueue.h"
#include "utils/New.h"

#include "Baselib.h"
#include "C/Baselib_Atomic.h"

namespace il2cpp
{
namespace utils
{
//
//  AtomicNode
//

    AtomicNode* AtomicNode::Link(AtomicNode* next)
    {
#if defined(IL2CPP_ATOMIC_HAS_QUEUE)
        AtomicNode* old = Next();
        Baselib_atomic_store_ptr_relaxed_v(&_next, &next);
        return old;
#else
        AtomicNode* old = Next();
        _next = (atomic_word)next;
        return old;
#endif
    }

#if defined(IL2CPP_ATOMIC_HAS_QUEUE)

#if !IL2CPP_TARGET_JAVASCRIPT

//
//  AtomicStack
//

    AtomicStack::AtomicStack()
    {
        atomic_word2 w;
        w.lo = w.hi = 0;
        Baselib_atomic_store_ptr2x_relaxed_v((void*)&_top, &w);
    }

    AtomicStack::~AtomicStack()
    {
    }

    int AtomicStack::IsEmpty() const
    {
        atomic_word2 top;
        Baselib_atomic_load_ptr2x_relaxed_v((void*)&_top, &top);
        return top.lo == 0;
    }

    void AtomicStack::Push(AtomicNode* node)
    {
        atomic_word2 top;
        Baselib_atomic_load_ptr2x_relaxed_v(&_top, &top);
        atomic_word2 newtop;

        newtop.lo = (atomic_word)node;
        do
        {
            Baselib_atomic_store_ptr_relaxed_v(&node->_next, &top.lo);
            newtop.hi = top.hi + 1;
        }
        while (!Baselib_atomic_compare_exchange_strong_ptr2x_release_relaxed_v(&_top, &top, &newtop));
    }

    void AtomicStack::PushAll(AtomicNode* first, AtomicNode* last)
    {
        atomic_word2 top;
        Baselib_atomic_load_ptr_relaxed_v(&_top, &top);
        atomic_word2 newtop;

        newtop.lo = (atomic_word)first;
        do
        {
            Baselib_atomic_store_ptr_relaxed_v(&last->_next, &top.lo);
            newtop.hi = top.hi + 1;
        }
        while (!Baselib_atomic_compare_exchange_strong_ptr2x_release_relaxed_v(&_top, &top, &newtop));
    }

    AtomicNode* AtomicStack::Pop()
    {
        atomic_word2 top;
        Baselib_atomic_load_ptr2x_relaxed_v(&_top, &top);
        atomic_word2 newtop;
        AtomicNode* node;

        do
        {
            node = (AtomicNode*)top.lo;
            if (!node)
                break;
            Baselib_atomic_load_ptr_relaxed_v(&node->_next, &newtop.lo);
            newtop.hi = top.hi + 1;
        }
        while (!Baselib_atomic_compare_exchange_strong_ptr2x_acquire_relaxed_v(&_top, &top, &newtop));

        return node;
    }

    AtomicNode* AtomicStack::PopAll()
    {
        atomic_word2 top;
        Baselib_atomic_load_ptr2x_relaxed_v(&_top, &top);
        atomic_word2 newtop;
        AtomicNode* node;

        do
        {
            node = (AtomicNode*)top.lo;
            if (!node)
                break;
            newtop.lo = 0;
            newtop.hi = top.hi + 1;
        }
        while (!Baselib_atomic_compare_exchange_strong_ptr2x_acquire_relaxed_v(&_top, &top, &newtop));

        return node;
    }

    AtomicStack* CreateAtomicStack()
    {
        // should be properly aligned
        return new(sizeof(atomic_word2)) AtomicStack;
    }

    void DestroyAtomicStack(AtomicStack* s)
    {
        delete s;
    }

//
//  AtomicQueue
//

    AtomicQueue::AtomicQueue()
    {
        AtomicNode* dummy = new AtomicNode;

        atomic_word zero = 0;
        atomic_word2 w;
        w.lo = (atomic_word)dummy;
        w.hi = 0;
        Baselib_atomic_store_ptr_relaxed_v(&dummy->_next, &zero);
        Baselib_atomic_store_ptr2x_relaxed_v(&_tail, &w);
        Baselib_atomic_store_ptr_release_v(&_head, &dummy);
    }

    AtomicQueue::~AtomicQueue()
    {
        AtomicNode* dummy;
        Baselib_atomic_load_ptr_relaxed_v(&_head, &dummy);
        delete dummy;
    }

    int AtomicQueue::IsEmpty() const
    {
        atomic_word2 cmp;
        Baselib_atomic_load_ptr2x_relaxed_v((void*)&_tail, &cmp);

        atomic_word next;
        Baselib_atomic_load_ptr_relaxed_v(&((AtomicNode*)cmp.lo)->_next, &next);
        return next == 0;
    }

    void AtomicQueue::Enqueue(AtomicNode* node)
    {
        AtomicNode* prev;

        atomic_word zero = 0;
        Baselib_atomic_store_ptr_relaxed_v(&node->_next, &zero);
        Baselib_atomic_exchange_ptr_release_v(&_head, &node, &prev);
        Baselib_atomic_store_ptr_release_v(&prev->_next, &node);
    }

    void AtomicQueue::EnqueueAll(AtomicNode* first, AtomicNode* last)
    {
        atomic_word zero = 0;
        Baselib_atomic_store_ptr_relaxed_v(&last->_next, &zero);

        AtomicNode* prev;

        Baselib_atomic_exchange_ptr_release_v(&_head, &last, &prev);
        Baselib_atomic_store_ptr_release_v(&prev->_next, &first);
    }

    AtomicNode* AtomicQueue::Dequeue()
    {
        AtomicNode* res, * next;
        void* data0;
        void* data1;
        void* data2;

        atomic_word2 tail;
        Baselib_atomic_load_ptr2x_relaxed_v(&_tail, &tail);
        atomic_word2 newtail;
        do
        {
            res = (AtomicNode*)tail.lo;
            Baselib_atomic_load_ptr_relaxed_v(&res->_next, &next);
            if (next == 0)
                return NULL;
            data0 = next->data[0];
            data1 = next->data[1];
            data2 = next->data[2];
            newtail.lo = (atomic_word)next;
            newtail.hi = tail.hi + 1;
        }
        while (!Baselib_atomic_compare_exchange_strong_ptr2x_seq_cst_relaxed_v(&_tail, &tail, &newtail));

        res->data[0] = data0;
        res->data[1] = data1;
        res->data[2] = data2;

        return res;
    }

    AtomicQueue* CreateAtomicQueue()
    {
        // UNITY_NEW can be used when it starts supporting alignof (instead of default alignement)
        return new(sizeof(atomic_word2)) AtomicQueue;
    }

    void DestroyAtomicQueue(AtomicQueue* s)
    {
        delete s;
    }

//
//  AtomicList
//

    void AtomicList::Init()
    {
        atomic_word2 zero;
        zero.lo = zero.hi = 0;
        Baselib_atomic_store_ptr2x_relaxed_v((void*)&_top, &zero);
    }

    atomic_word AtomicList::Tag()
    {
        atomic_word2 w;
        Baselib_atomic_load_ptr2x_relaxed_v((void*)&_top, &w);

        return w.hi;
    }

    AtomicNode* AtomicList::Peek()
    {
        atomic_word2 w;
        Baselib_atomic_load_ptr2x_relaxed_v((void*)&_top, &w);

        return (AtomicNode*)w.lo;
    }

    AtomicNode* AtomicList::Load(atomic_word &tag)
    {
        atomic_word2 w;
        Baselib_atomic_load_ptr2x_relaxed_v((void*)&_top, &w);
        tag = w.hi;

        return (AtomicNode*)w.lo;
    }

    bool AtomicList::Add(AtomicNode *first, AtomicNode *last, atomic_word tag)
    {
        atomic_word2 oldval, newval;
        bool res = false;

        newval.lo = (atomic_word)first;
        newval.hi = tag;

        Baselib_atomic_load_ptr2x_relaxed_v((void*)&_top, &oldval);
        while (oldval.hi == tag)
        {
            last->Link((AtomicNode*)oldval.lo);
            res = Baselib_atomic_compare_exchange_strong_ptr2x_acq_rel_relaxed_v((void*)&_top, &oldval, &newval);
            if (res)
            {
                break;
            }
        }
        return res;
    }

    AtomicNode* AtomicList::Touch(atomic_word tag)
    {
        atomic_word2 w, r;
        w.lo = 0;
        w.hi = tag;
        Baselib_atomic_exchange_ptr2x_acq_rel_v(&_top, &w, &r);
        w = r;

        return (AtomicNode*)w.lo;
    }

    void AtomicList::Reset(AtomicNode* node, atomic_word tag)
    {
        atomic_word2 w;
        w.lo = (atomic_word)node;
        w.hi = tag;
        Baselib_atomic_store_ptr2x_relaxed_v(&_top, &w);
    }

    AtomicNode* AtomicList::Clear(AtomicNode* old, atomic_word tag)
    {
        atomic_word2 top;
        atomic_word2 newtop;
        top.lo = (atomic_word)old;
        top.hi = tag;
        newtop.lo = 0;
        newtop.hi = tag + 1;

        if (Baselib_atomic_compare_exchange_strong_ptr2x_acquire_relaxed_v(&_top, &top, &newtop))
        {
            return (AtomicNode*)top.lo;
        }
        else
        {
            return NULL;
        }
    }

#else // !defined(IL2CPP_ATOMIC_HAS_QUEUE)

//
//  AtomicList
//

    void AtomicList::Init()
    {
        _top = 0;
        _ver = 0;
    }

    atomic_word AtomicList::Tag()
    {
        return _ver;
    }

    AtomicNode* AtomicList::Peek()
    {
        return (AtomicNode*)_top;
    }

    AtomicNode* AtomicList::Load(atomic_word &tag)
    {
        tag = _ver;
        return (AtomicNode*)_top;
    }

    bool AtomicList::Add(AtomicNode *first, AtomicNode *last, atomic_word tag)
    {
        last->Link((AtomicNode*)_top);
        _top = (atomic_word)first;
        return true;
    }

    AtomicNode* AtomicList::Touch(atomic_word tag)
    {
        AtomicNode* res = (AtomicNode*)_top;
        _top = 0;
        _ver = tag;
        return res;
    }

    void AtomicList::Reset(AtomicNode* node, atomic_word tag)
    {
        _top = (atomic_word)node;
        _ver = tag;
    }

    AtomicNode* AtomicList::Clear(AtomicNode* old, atomic_word tag)
    {
        if (_top == (atomic_word)old && _ver == tag)
        {
            _top = 0;
            ++_ver;
            return old;
        }
        else
        {
            return NULL;
        }
    }

#endif

#endif // !IL2CPP_TARGET_JAVASCRIPT
} // utils
} // il2cpp

#endif
