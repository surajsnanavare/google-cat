/*
 * ValueThing.java
 *
 * Copyright (c) 2007 Operational Dynamics Consulting Pty Ltd
 * 
 * The code in this file, and the program it is a part of, are made available
 * to you by the authors under the terms of the "GNU General Public Licence,
 * version 2" See the LICENCE file for the terms governing usage and
 * redistribution.
 */
package com.operationaldynamics.codegen;

import com.operationaldynamics.driver.DefsFile;

/**
 * Hard coded Thing type for GValues, mostly here so that we can put
 * <code>valueFor()</code> in as the translation code.
 * 
 * @author Andrew Cowie
 */
public class ValueThing extends ProxiedThing
{
    /*
     * Covers off requirement for a nullary constructor which in other Thing
     * subclasses we have a protected constructor for.
     */
    public ValueThing() {
        super("G_VALUE_TYPE", "GValue*", "oscats.glib", "GValue", "Value");
    }

    String translationToJava(String name, DefsFile data) {
        return "valueFor(" + name + ")";
    }
}
