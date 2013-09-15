/* -*- mode: C; c-file-style: "gnu"; indent-tabs-mode: nil; -*-
 *
 * Copyright (C) 2013 Colin Walters <walters@verbum.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#pragma once

#include "ostree-repo.h"
#include "ostree-deployment.h"
#include "ostree-bootloader.h"

G_BEGIN_DECLS

#define OSTREE_TYPE_SYSROOT ostree_sysroot_get_type()
#define OSTREE_SYSROOT(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj), OSTREE_TYPE_SYSROOT, OstreeSysroot))
#define OSTREE_IS_SYSROOT(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), OSTREE_TYPE_SYSROOT))

GType ostree_sysroot_get_type (void);

OstreeSysroot* ostree_sysroot_new (GFile *path);

OstreeSysroot* ostree_sysroot_new_default (void);

GFile *ostree_sysroot_get_path (OstreeSysroot *self);

gboolean ostree_sysroot_ensure_initialized (OstreeSysroot  *self,
                                            GCancellable   *cancellable,
                                            GError        **error);

gboolean ostree_sysroot_read_current_subbootversion (OstreeSysroot *self,
                                                     int            bootversion,
                                                     int           *out_subbootversion,
                                                     GCancellable  *cancellable,
                                                     GError       **error);

gboolean ostree_sysroot_list_deployments (OstreeSysroot       *self,
                                          int                 *out_bootversion,
                                          GPtrArray          **out_deployments,
                                          GCancellable        *cancellable,
                                          GError             **error);

GFile *ostree_sysroot_get_deployment_directory (OstreeSysroot    *self,
                                                OstreeDeployment *deployment);

GFile * ostree_sysroot_get_deployment_origin_path (GFile   *deployment_path);

gboolean ostree_sysroot_cleanup (OstreeSysroot       *self,
                                 GCancellable        *cancellable,
                                 GError             **error);

gboolean ostree_sysroot_get_repo (OstreeSysroot         *self,
                                  OstreeRepo           **out_repo,
                                  GCancellable          *cancellable,
                                  GError               **error);

OstreeBootloader *ostree_sysroot_query_bootloader (OstreeSysroot         *sysroot);


G_END_DECLS
