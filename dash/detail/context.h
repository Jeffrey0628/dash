
/* Copyright (c) 2011-2012, EPFL/Blue Brain Project
 *                     Stefan Eilemann <stefan.eilemann@epfl.ch>
 *
 * This file is part of DASH <https://github.com/BlueBrain/dash>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef DASH_DETAIL_CONTEXT_H
#define DASH_DETAIL_CONTEXT_H

#include "types.h"
#include "contextCommit.h"

#include <dash/api.h>
#include <lunchbox/lfVector.h> // member
#include <lunchbox/types.h>

namespace dash
{
namespace detail
{

/** Internal implementation of the dash::Context */
class Context
{
public:
    Context(); //!< Create a new context
    ~Context();

    DASH_API static Context& getCurrent();

    DASH_API static size_t getNumSlots();
    size_t getSlot() const { return slot_; }

    void map( dash::NodePtr node, const Context& to );
    void unmap( dash::NodePtr node );

    void map( AttributePtr attribute, const Context& to );
    void unmap( AttributePtr attribute );

    void addChange( const ContextChange& change );
    dash::Commit commit();
    void apply( ConstCommitPtr commit );

private:
    friend int ::testMain( int, char ** );

    const size_t slot_; //!< lookup index for data of this Context
    ContextCommit commit_; //!< pending changes

    Context( const Context& from ); // disable copy
    Context& operator = ( const Context& from ); // disable assignment

    LB_TS_VAR( thread_ )
};

}
}

#endif // DASH_DETAIL_CONTEXT_H
