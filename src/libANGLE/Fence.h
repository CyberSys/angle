//
// Copyright (c) 2002-2013 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// Fence.h: Defines the gl::FenceNV and gl::FenceSync classes, which support the GL_NV_fence
// extension and GLES3 sync objects.

#ifndef LIBANGLE_FENCE_H_
#define LIBANGLE_FENCE_H_

#include "libANGLE/Error.h"
#include "libANGLE/RefCountObject.h"
#include "libANGLE/export.h"

#include "common/angleutils.h"

namespace rx
{
class FenceNVImpl;
class FenceSyncImpl;
}

namespace gl
{

class ANGLE_EXPORT FenceNV
{
  public:
    explicit FenceNV(rx::FenceNVImpl *impl);
    virtual ~FenceNV();

    GLboolean isFence() const;
    Error setFence(GLenum condition);
    Error testFence(GLboolean *outResult);
    Error finishFence();

    GLboolean getStatus() const { return mStatus; }
    GLuint getCondition() const { return mCondition; }

  private:
    DISALLOW_COPY_AND_ASSIGN(FenceNV);

    rx::FenceNVImpl *mFence;

    bool mIsSet;

    GLboolean mStatus;
    GLenum mCondition;
};

class ANGLE_EXPORT FenceSync : public RefCountObject
{
  public:
    explicit FenceSync(rx::FenceSyncImpl *impl, GLuint id);
    virtual ~FenceSync();

    Error set(GLenum condition);
    Error clientWait(GLbitfield flags, GLuint64 timeout, GLenum *outResult);
    Error serverWait(GLbitfield flags, GLuint64 timeout);
    Error getStatus(GLint *outResult) const;

    GLuint getCondition() const { return mCondition; }

  private:
    DISALLOW_COPY_AND_ASSIGN(FenceSync);

    rx::FenceSyncImpl *mFence;

    GLenum mCondition;
};

}

#endif   // LIBANGLE_FENCE_H_
