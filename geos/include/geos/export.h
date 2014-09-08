/**********************************************************************
 *
 * GEOS - Geometry Engine Open Source
 * http://geos.osgeo.org
 *
 * Copyright (C) 2009   Ragi Y. Burhum <ragi@burhum.com>
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation.
 * See the COPYING file for more information.
 *
 **********************************************************************/
#ifndef GEOS_EXPORT_H
#define GEOS_EXPORT_H

#include <QtGlobal>

#if defined(GEOS_DLL_EXPORT)
#  define GEOS_DLL   Q_DECL_EXPORT
#elif defined(GEOS_DLL_IMPORT)
#  define GEOS_DLL   Q_DECL_IMPORT
#else
#  define GEOS_DLL
#endif

#endif
