package org.msgpack.util.codegen;

import org.msgpack.MessageUnpacker;

public class DynamicCodeGenUnpacker {
	public static MessageUnpacker create(Class<?> c) {
		try {
			DynamicCodeGen gen = DynamicCodeGen.getInstance();
			Class<?> unpackerClass = gen.generateMessageUnpackerClass(c);
			return (MessageUnpacker) unpackerClass.newInstance();
		} catch (InstantiationException e) {
			throw new DynamicCodeGenException(e.getMessage(), e);
		} catch (IllegalAccessException e) {
			throw new DynamicCodeGenException(e.getMessage(), e);
		}
	}
}
