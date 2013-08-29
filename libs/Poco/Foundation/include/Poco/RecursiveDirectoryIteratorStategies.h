// From: http://sourceforge.net/p/poco/feature-requests/168/
//
// RecursiveDirectoryIteratorStategies.h
//
// $Id$
//
// Library: Foundation
// Package: Filesystem
// Module:  RecursiveDirectoryIterator
//
// Definitions of the RecursiveDirectoryIterator stategy classes.
//
// Copyright (c) 2012, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Foundation_RecursiveDirectoryIteratorStategies_INCLUDE
#define Foundation_RecursiveDirectoryIteratorStategies_INCLUDE


#include "Poco/Foundation.h"
#include "Poco/DirectoryIterator.h"
#include <stack>
#include <queue>
#include <functional>


namespace Poco {


    class TraverseBase
    {
    public:
        typedef std::stack<DirectoryIterator> Stack;
        typedef std::pointer_to_unary_function<const Stack&, UInt16> DepthFunPtr;

        enum { D_INFINITE = 0 };
        /// Constant for infinite traverse depth.

        TraverseBase(DepthFunPtr depthDeterminer, UInt16 maxDepth = D_INFINITE);

    protected:
        bool isFiniteDepth();

        DepthFunPtr _depthDeterminer;
        UInt16 _maxDepth;

        DirectoryIterator _itEnd;

    private:
        TraverseBase();
        TraverseBase(const TraverseBase&);
        TraverseBase& operator= (const TraverseBase&);
    };


    class ChildrenFirstTraverse : public TraverseBase
    {
    public:
        ChildrenFirstTraverse(DepthFunPtr depthDeterminer, UInt16 maxDepth = D_INFINITE);

        const std::string next(Stack* itStack, bool* isFinished);

    private:
        ChildrenFirstTraverse();
        ChildrenFirstTraverse(const ChildrenFirstTraverse&);
        ChildrenFirstTraverse& operator= (const ChildrenFirstTraverse&);
    };


    class SiblingsFirstTraverse : public TraverseBase
    {
    public:
        SiblingsFirstTraverse(
                              DepthFunPtr depthDeterminer, UInt16 maxDepth = D_INFINITE);

        const std::string next(Stack* itStack, bool* isFinished);
        
    private:
        SiblingsFirstTraverse();
        SiblingsFirstTraverse(const SiblingsFirstTraverse&);
        SiblingsFirstTraverse& operator= (const SiblingsFirstTraverse&);
        
        std::stack< std::queue<std::string> > _dirsStack;
    };
    
    
} // namespace Poco


#endif // Foundation_RecursiveDirectoryIteratorStategies_INCLUDE