//
// MessagePack for Java
//
// Copyright (C) 2009 FURUHASHI Sadayuki
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//
package org.msgpack.schema;

import java.io.IOException;
import org.msgpack.*;

public class ByteSchema extends Schema {
	public ByteSchema() {
		super("Byte");
	}

	@Override
	public String getExpression() {
		return "byte";
	}

	@Override
	public void pack(Packer pk, Object obj) throws IOException {
		if(obj instanceof Number) {
			pk.packByte( ((Number)obj).byteValue() );

		} else if(obj == null) {
			pk.packNil();

		} else {
			throw MessageTypeException.invalidConvert(obj, this);
		}
	}

	@Override
	public Object convert(Object obj) throws MessageTypeException {
		if(obj instanceof Byte) {
			return obj;

		} else if(obj instanceof Number) {
			return ((Number)obj).byteValue();

		} else {
			throw MessageTypeException.invalidConvert(obj, this);
		}
	}

	@Override
	public Object createFromByte(byte v) {
		return (byte)v;
	}

	@Override
	public Object createFromShort(short v) {
		return (byte)v;
	}

	@Override
	public Object createFromInt(int v) {
		return (byte)v;
	}

	@Override
	public Object createFromLong(long v) {
		return (byte)v;
	}

	@Override
	public Object createFromFloat(float v) {
		return (byte)v;
	}

	@Override
	public Object createFromDouble(double v) {
		return (byte)v;
	}
}

