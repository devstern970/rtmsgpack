//
// MessagePack for Java
//
// Copyright (C) 2009-2010 FURUHASHI Sadayuki
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
package org.msgpack.template;

import java.io.IOException;
import org.msgpack.*;

public class StringTemplate implements Template {
	private StringTemplate() { }

	public void pack(Packer pk, Object target) throws IOException {
		pk.packString((String)target);
	}

	public Object unpack(Unpacker pac) throws IOException, MessageTypeException {
		return pac.unpackString();
	}

	public Object convert(MessagePackObject from) throws MessageTypeException {
		return from.asString();
	}

	static public StringTemplate getInstance() {
		return instance;
	}

	static final StringTemplate instance = new StringTemplate();

	static {
		CustomMessage.register(String.class, instance);
	}
}

