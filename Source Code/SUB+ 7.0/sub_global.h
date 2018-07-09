#ifndef SUB_GLOBAL_H
#define SUB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SUB_LIBRARY)
#  define SUBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SUBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SUB_GLOBAL_H
