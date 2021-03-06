#include "Token.hpp"

namespace
{
	static constexpr const char* typeMap[] =
	{
		// Primitive Values
		"ValueInteger",
		"ValueFloat",
		"ValueChar",
		"ValueString",
		"ValueBool",

		// Type modifiers
		"TypePointer",
		"TypeFunction",
		"TypeArray",

		// Memory Operations
		"MemoryAllocate",
		"MemoryDeallocate",

		/* Operators */

		// arithmetic
		"OperatorAdd",
		"OperatorSub",
		"OperatorMult",
		"OperatorDiv",
		"OperatorMod",

		// Bitwise
		"OperatorBitwiseAnd",
		"OperatorBitwiseOr",
		"OperatorBitwiseXor",
		"OperatorBitwiseNot",

		// Bitshift
		"OperatorBitshiftLeft",
		"OperatorBitshiftRight",

		// Relational
		"OperatorEqual",
		"OperatorNotEqual",
		"OperatorLesser",
		"OperatorGreater",
		"OperatorLesserEqual",
		"OperatorGreaterEqual",

		// Logical
		"OperatorAnd",
		"OperatorOr",
		"OperatorXor",
		"OperatorNot",

		// Assignment
		"OperatorAssign",
		"OperatorAddAssign",
		"OperatorSubAssign",
		"OperatorMultAssign",
		"OperatorDivAssign",
		"OperatorModAssign",
		"OperatorBitwiseAndAssign",
		"OperatorBitwiseOrAssign",
		"OperatorBitwiseXorAssign",
		"OperatorBitwiseNotAssign",
		"OperatorBitshiftLeftAssign",
		"OperatorBitshiftRightAssign",

		// increment/decrement
		"Increment",
		"Decrement",

		// Memory
		"OperatorAddressOf",
		"OperatorDereference",

		// Comments
		"LineComment",
		"BlockComment",

		// Symbols
		"SymbolOpenParen",
		"SymbolEndParen",
		"SymbolOpenSquareBracket",
		"SymbolEndSquareBracket",
		"SymbolOpenCurlyBrace",
		"SymbolEndCurlyBrace",
		"SymbolOpenAngleBracket",
		"SymbolEndAngleBracket",
		"SymbolSingleQuote",
		"SymbolDoubleQuote",

		"Identifier",
	};
}

namespace dbr
{
	namespace sl
	{
		Token::Token(Type t)
		:	type(t)
		{}

		const char* Token::asString()
		{
			return typeMap[static_cast<std::size_t>(type)];
		}
	}
}