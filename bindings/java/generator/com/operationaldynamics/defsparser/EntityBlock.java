/*
 * EntityBlock.java
 *
 * Copyright (c) 2007-2008 Operational Dynamics Consulting Pty Ltd, and Others
 * 
 * The code in this file, and the program it is a part of, are made available
 * to you by the authors under the terms of the "GNU General Public Licence,
 * version 2" See the LICENCE file for the terms governing usage and
 * redistribution.
 */
package com.operationaldynamics.defsparser;

import java.util.List;

import com.operationaldynamics.codegen.EntityGenerator;
import com.operationaldynamics.codegen.EntityThing;
import com.operationaldynamics.codegen.Generator;
import com.operationaldynamics.codegen.Thing;
import com.operationaldynamics.driver.DefsFile;

/**
 * Block object representing the .defs data defining the entities in
 * (currently) the Cairo library. The key feature is forcing the bindings
 * class name to be wildly different than the wacko C side name.
 * 
 * @author Andrew Cowie
 */
public class EntityBlock extends TypeBlock
{
    public EntityBlock(final String blockName, final List<String[]> characteristics) {
        super(blockName, characteristics);
    }

    public Thing createThing() {
        final String bindingsPackage;
        final EntityThing t;

        bindingsPackage = moduleToJavaPackage(inModule);

        if (bindingsPackage.equals("org.freedesktop.enchant")) {
            t = new EntityThing(gtypeId, addPointerSymbol(cName), bindingsPackage, cName, blockName);
        } else {
            /*
             * Note that we're not using cName here; it's cairo_t and not
             * suitable as a generated bindings layer class name.
             */
            t = new EntityThing(gtypeId, addPointerSymbol(cName), bindingsPackage, inModule + blockName,
                    blockName);
        }

        t.setImportHeader(importHeader);
        return t;
    }

    public Generator createGenerator(final DefsFile data) {
        return new EntityGenerator(data);
    }
}
