/*
 * GlibMisc.java
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
package oscats.glib;

import oscats.glib.Plumbing;

final class GlibMisc extends Plumbing
{
    private GlibMisc() {}

    static final void setPrgname(String prgname) {
        if (prgname == null) {
            throw new IllegalArgumentException("prgname can't be null");
        }

        {
            g_set_prgname(prgname);
        }
    }

    private static native final void g_set_prgname(String prgname);
}

