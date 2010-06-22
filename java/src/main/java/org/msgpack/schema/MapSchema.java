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
package org.msgpack.schema;

import java.util.Map;
import java.util.HashMap;
import java.io.IOException;
import org.msgpack.*;

public class MapSchema extends Schema implements IMapSchema {
	private Schema keySchema;
	private Schema valueSchema;

	public MapSchema(Schema keySchema, Schema valueSchema) {
		this.keySchema = keySchema;
		this.valueSchema = valueSchema;
	}

	@Override
	public String getClassName() {
		return "Map<"+keySchema.getClassName()+", "+valueSchema.getClassName()+">";
	}

	@Override
	public String getExpression() {
		return "(map "+keySchema.getExpression()+" "+valueSchema.getExpression()+")";
	}

	@Override
	@SuppressWarnings("unchecked")
	public void pack(Packer pk, Object obj) throws IOException {
		if(obj instanceof Map) {
			Map<Object,Object> d = (Map<Object,Object>)obj;
			pk.packMap(d.size());
			for(Map.Entry<Object,Object> e : d.entrySet()) {
				keySchema.pack(pk, e.getKey());
				valueSchema.pack(pk, e.getValue());
			}
		} else if(obj == null) {
			pk.packNil();
		} else {
			throw MessageTypeException.invalidConvert(obj, this);
		}
	}

	@SuppressWarnings("unchecked")
	public static final <K,V> Map<K,V> convertMap(Object obj,
			Schema keySchema, Schema valueSchema, Map<K,V> dest) throws MessageTypeException {
		if(!(obj instanceof Map)) {
			throw new MessageTypeException();
		}
		Map<Object,Object> d = (Map<Object,Object>)obj;
		if(dest == null) {
			dest = new HashMap<K,V>(d.size());
		}
		for(Map.Entry<Object,Object> e : d.entrySet()) {
			dest.put((K)keySchema.convert(e.getKey()),
					(V)valueSchema.convert(e.getValue()));
		}
		return (Map<K,V>)d;
	}

	@Override
	public Object convert(Object obj) throws MessageTypeException {
		return convertMap(obj, keySchema, valueSchema, null);
	}

	@Override
	public Schema getKeySchema() {
		return keySchema;
	}

	@Override
	public Schema getValueSchema() {
		return valueSchema;
	}

	@Override
	@SuppressWarnings("unchecked")
	public Object createFromMap(Object[] obj) {
		HashMap dest = new HashMap(obj.length / 2);
		int i = 0;
		while(i < obj.length) {
			Object k = obj[i++];
			Object v = obj[i++];
			dest.put(k, v);
		}
		return dest;
	}
}

