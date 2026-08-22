// gdxms2_converter.cpp

#include "gdxms2_converter.hpp"

MiniScript::Value var_to_val(godot::Variant v) {
	switch (v.get_type()){
		// nil -> Null
		case godot::Variant::NIL:
			return MiniScript::Value();

		// bool/int/float -> Number
		case godot::Variant::BOOL:
		case godot::Variant::INT:
		case godot::Variant::FLOAT:
			return MiniScript::Value(double(v));

		// String -> String
		case godot::Variant::STRING:
			return MiniScript::Value::make_string(godot::String(v).utf8());

		// TODO: Unimplemented
		case godot::Variant::VECTOR2:
		case godot::Variant::VECTOR2I:
		case godot::Variant::RECT2:
		case godot::Variant::RECT2I:
		case godot::Variant::VECTOR3:
		case godot::Variant::VECTOR3I:
		case godot::Variant::TRANSFORM2D:
		case godot::Variant::VECTOR4:
		case godot::Variant::VECTOR4I:
		case godot::Variant::PLANE:
		case godot::Variant::QUATERNION:
		case godot::Variant::AABB:
		case godot::Variant::BASIS:
		case godot::Variant::TRANSFORM3D:
		case godot::Variant::PROJECTION:
		case godot::Variant::COLOR:
			return MiniScript::Value();

		// StringName -> String
		case godot::Variant::STRING_NAME:
			return MiniScript::Value::make_string(godot::String(godot::StringName(v)).utf8());

		// NodePath -> String
		case godot::Variant::NODE_PATH:
			return MiniScript::Value::make_string(godot::String(godot::NodePath(v)).utf8());

		// RID -> Number
		case godot::Variant::RID:
			return MiniScript::Value(double(godot::RID(v).get_id()));

		// TODO: Unimplemented
		case godot::Variant::OBJECT:
			return MiniScript::Value();

		// Callable -> FuncDef
		case godot::Variant::CALLABLE: {
			godot::Callable c(v);
			godot::String name(godot::StringName(c.get_method()));
			MiniScript::Intrinsic f = MiniScript::Intrinsic::New();
			f.set_Name(MiniScript::String(name.utf8()));
			for (int i=0; i<c.get_argument_count(); i++){
				f.AddParam("arg"+MiniScript::ToString(i));
			}
			f.set_Code([c](MiniScript::Context ctx, MiniScript::IntrinsicResult) -> MiniScript::IntrinsicResult {
				int size = ctx.argCount;
				godot::Array args;
				args.resize(size);
				for (int i=0; i<size; i++){
					args[i]=val_to_var(ctx.GetArg(i));
				}
				return MiniScript::IntrinsicResult(var_to_val(c.callv(args)));
			});
			return f.GetFunc();
		}

		// Signal -> Null (You aren't supposed to own this)
		case godot::Variant::SIGNAL:
			return MiniScript::Value();

		case godot::Variant::DICTIONARY: {
			godot::Dictionary dic(v);
			godot::Array keys = dic.keys();
			godot::Array vals = dic.values();

			MiniScript::Value map = MiniScript::Value::make_map(dic.size());
			for (int i=0; i<map.MapCount(); i++){
				map.MapSet(var_to_val(keys[i]), var_to_val(vals[i]));
			}
			return map;

		}
		// Array types -> List @ TODO: Make type-specific implementation for each packed array to avoid runtime type parsing
		case godot::Variant::ARRAY:
		case godot::Variant::PACKED_BYTE_ARRAY:
		case godot::Variant::PACKED_COLOR_ARRAY:
		case godot::Variant::PACKED_FLOAT32_ARRAY:
		case godot::Variant::PACKED_FLOAT64_ARRAY:
		case godot::Variant::PACKED_INT32_ARRAY:
		case godot::Variant::PACKED_INT64_ARRAY:
		case godot::Variant::PACKED_STRING_ARRAY:
		case godot::Variant::PACKED_VECTOR2_ARRAY:
		case godot::Variant::PACKED_VECTOR3_ARRAY:
		case godot::Variant::PACKED_VECTOR4_ARRAY:
		{
			godot::Array arr(v);
			int size = arr.size();
			MiniScript::Value list = MiniScript::Value::make_list(size);
			for (int i=0; i<size; i++){
				list.ListSet(i, var_to_val(arr[i]));
			}
			return list;
		}

		// Default case (this will never trigger unless you define a custom variant)
		default:
			return MiniScript::Value();

	}
}

godot::Variant val_to_var(MiniScript::Value v) {
	switch (v.Type()) {

		// Null -> nil
		case MiniScript::ValueType::Null:
			return godot::Variant();

		// Number -> double
		case MiniScript::ValueType::Number:
			return godot::Variant(v.AsDouble());

		// String -> String
		case MiniScript::ValueType::String:
			return godot::String(v.c_str());

		// List -> Array
		case MiniScript::ValueType::List: {
			int size = v.ListCount();
			godot::Array arr;
			arr.resize(size);

			for (int i=0; i<size; i++){
				arr[i] = val_to_var(v.ListGet(i));
			}

			return arr;
		}

		// Map -> Dictionary
		case MiniScript::ValueType::Map: {
			godot::Dictionary dic;
			MiniScript::GCMap map = MiniScript::GCManager::GetMap(v);

			for (int i = 0; i<v.MapCount(); i++){
				dic.set(val_to_var(map.KeyAt(i)), (val_to_var(map.ValueAt(i))));
			}

			return dic;
		}

		// Not implemented yet -- require custom classes @ TODO add custom classes for conversion
		case MiniScript::ValueType::Function:
		case MiniScript::ValueType::Handle:
		case MiniScript::ValueType::Error:
			return godot::Variant();

	}
}
