/* register_types.cpp */

#include "register_types.h"

#include "core/class_db.h"
#include "PXLua.h"

void register_luajitpx_types() {
    ClassDB::register_class<PXLua>();
}

void unregister_luajitpx_types() {
   //nothing to do here
}