/*
 * This file is part of the OregonCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef  OREGON_REFERENCE_H
#define  OREGON_REFERENCE_H

/*
 * Referencer is an object that holds a reference holder that  hold a reference
 * counted object.  When an object's reference count drop to zero, it removes
 * the object.  This is a non intrusive mechanism and any object at any point
 * in time can be referenced.  When and object is reference counted, do not
 * pass the object directly to other methods but rather, pass its
 * reference around.  Objects can be reference counted in both single threaded
 * model and multi-threaded model
 */

#include <stdexcept>
#include "Define.h"
#include "ThreadingModel.h"
#include "ReferenceHolder.h"

template
<
    typename T,
    class THREADING_MODEL = Oregon::SingleThreaded<T>
    >
class Referencer
{
        typedef typename THREADING_MODEL::Lock Lock;
        typedef ReferenceHolder<T, THREADING_MODEL> ReferenceeHolder;
    public:

        // Constructs a referencer.
        Referencer(T* ref = NULL);

        // Copy constructor
        Referencer(const Referencer& obj) : i_holder(NULL)
        {
            *this = obj;
        }

        // Destructor
        ~Referencer();

        // Referencee accessor
        T* referencee(void)
        {
            return (i_holder == NULL ? NULL : i_holder->i_referencee);
        }
        const T* referencee(void) const
        {
            return (i_holder == NULL ? NULL : i_holder->i_referencee);
        }

        //T& referencee(void){ return _referencee(); }
        //const T& referencee(void) const { return const_cast<Referencer *>(this)->_referencee(); }
        operator T& (void)
        {
            return _referencee();
        }
        operator const T& (void) const
        {
            return *const_cast<Referencer*>(this)->_referencee();
        }

        // cast operators
        T* operator*()
        {
            return (i_holder == NULL ? NULL : i_holder->i_referencee);
        }
        T const* operator*() const
        {
            return (i_holder == NULL ? NULL : i_holder->i_referencee);
        }

        // overload operators
        T* operator->()
        {
            return (i_holder == NULL ? NULL : i_holder->i_referencee);
        }
        const T* operator->() const
        {
            return (i_holder == NULL ? NULL : i_holder->i_referencee);
        }

        // operator =
        Referencer& operator=(const Referencer& obj);
        Referencer& operator=(T*);

        // returns true if i_referencee is null
        bool isNull(void) const
        {
            return i_holder == NULL;
        }

    private:

        T& _referencee(void)
        {
            if (i_holder == NULL)
                throw std::runtime_error("Invalid access to null pointer");
            return *i_holder->i_referencee;
        }

        void deReference(ReferenceeHolder*);
        void addReference(ReferenceeHolder*);

        // private data
        ReferenceeHolder* i_holder;
};
#endif

