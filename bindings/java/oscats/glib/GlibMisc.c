/*
 * GlibMisc.c
 *
 * Copyright (c) 2006-2009 Operational Dynamics Consulting Pty Ltd, and Others
 *
 * The code in this file, and the program it is a part of, are made available
 * to you by the authors under the terms of the "GNU General Public Licence,
 * version 2" plus the "Classpath Exception" (you may link to this code as a
 * library into other programs provided you don't make a derivation of it).
 * See the LICENCE file for the terms governing usage and redistribution.
 *
 *                      THIS FILE IS GENERATED CODE!
 *
 * To modify its contents or behaviour, either update the generation program,
 * change the information in the source defs file, or implement an override for
 * this class.
 */

#include <jni.h>
#include <oscats.h>
#include "bindings_java.h"
#include "oscats_glib_GlibMisc.h"

JNIEXPORT void JNICALL
Java_org_gnome_glib_GlibMisc_g_1set_1prgname
(
	JNIEnv* env,
	jclass cls,
	jstring _prgname
)
{
	const gchar* prgname;

	// convert parameter prgname
	prgname = (const gchar*) bindings_java_getString(env, _prgname);
	if (prgname == NULL) {
		return; // Java Exception already thrown
	}

	// call function
	g_set_prgname(prgname);

	// cleanup parameter prgname
	bindings_java_releaseString(prgname);
}
