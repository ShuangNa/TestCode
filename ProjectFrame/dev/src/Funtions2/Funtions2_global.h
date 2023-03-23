#ifndef FUNTIONS2_GLOBAL_H
#define FUNTIONS2_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FUNTIONS2_LIBRARY)
#  define FUNTIONS2_EXPORT Q_DECL_EXPORT
#else
#  define FUNTIONS2_EXPORT Q_DECL_IMPORT
#endif

#endif // FUNTIONS2_GLOBAL_H
