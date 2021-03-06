#ifndef DBR_SVM_INSTRUCTION_HPP
#define DBR_SVM_INSTRUCTION_HPP

#include <cstdint>
#include <vector>

namespace dbr
{
	namespace svm
	{
		/*
			An instruction is encoded in 8 bytes.

			byte 0:	instruction type (may be shrunk in the future. Not even coming close to using the whole byte)
			
			The rest of the bytes are the arguments, of which size and count depend on the argument

			bytes 1, 2, & 3 can be used as "arg 1x", returning a uint (32 bits), with a max of 24 bits being used

			bytes 2 & 3 can be used as "arg 2x", returning a ushort (16 bits), rather than a byte
			usually used to index into the constants table
		 */
		class Instruction
		{
		public:
			enum class Type : std::uint8_t
			{
				/* memory ops */
				Load,		// 1: write-to, 2: index
				LoadC,		// 1: write-to, 2x: constant index

				/* math ops */
				// integer
				Add,		// "addition" 1: write-to, 2: registry index, 3: registry index
				Sub,		// "subtraction" 1: write-to, 2: registry index, 3: registry index
				Mult,		// "multiplication" 1: write-to, 2: registry index, 3: registry index
				Div,		// "division" 1: write-to, 2: registry index, 3: registry index
				Mod,		// "modulus" 1: write-to, 2: registry index, 3: registry index
				Neg,		// "negative" 1: write-to, 2: registry index

				// float
				FAdd,		// "addition" 1: write-to, 2: registry index, 3: registry index
				FSub,		// "subtraction" 1: write-to, 2: registry index, 3: registry index
				FMult,		// "multiplication" 1: write-to, 2: registry index, 3: registry index
				FDiv,		// "division" 1: write-to, 2: registry index, 3: registry index
				FNeg,		// "negative" 1: write-to, 2: registry index

				// SIMD (Single-Instruction Multiple-Data)
				simdAdd,
				simdSub,
				simdMult,
				simdDiv,

				// misc
				CastI,		// "cast to int" 1: write-to, 2: index
				CastF,		// "cast to float" 1: write-to, 2: index

				/* comparison ops */
				// integer
				Lt,			// "less than" 1: write-to, 2: registry index, 3: registry index
				LtEq,		// "less than or equal" 1: write-to, 2: registry index, 3: registry index
				Gt,			// "greater than" 1: write-to, 2: registry index, 3: registry index
				GtEq,		// "greater than or equal" 1: write-to, 2: registry index, 3: registry index
				Eq,			// "equals" 1: write-to, 2: registry index, 3: registry index
				Neq,		// "not equals" 1: write-to, 2: registry index, 3: registry index

				// float
				FLt,		// "less than" 1: write-to, 2: registry index, 3: registry index
				FLtEq,		// "less than or equal" 1: write-to, 2: registry index, 3: registry index
				FGt,		// "greater than" 1: write-to, 2: registry index, 3: registry index
				FGtEq,		// "greater than or equal" 1: write-to, 2: registry index, 3: registry index
				FEq,		// "equals" 1: write-to, 2: registry index, 3: registry index
				FNeq,		// "not equals" 1: write-to, 2: registry index, 3: registry index

				/* logical ops */
				Not,		// 1: write-to, 2: registry index
				And,		// 1: write-to, 2: registry index, 3: registry index
				Or,			// 1: write-to, 2: registry index, 3: registry index
				Xor,		// 1: write-to, 2: registry index, 3: registry index

				/* bitwise ops */
				BNot,		// "bitwise not" 1: write-to, 2: registry index
				BAnd,		// "bitwise and" 1: write-to, 2: registry index, 3: registry index
				BOr,		// "bitwise or" 1: write-to, 2: registry index, 3: registry index
				BXor,		// "bitwise xor" 1: write-to, 2: registry index, 3: registry index
				Bsl,		// "bitwise shift left" 1: write-to, 2: registry index to shift, 3: registry index amount to shift by
				Bsr,		// "bitwise shift right" 1: write-to, 2: registry index to shift, 3: registry index amount to shift by

				/* conditional branching */
				// absolute jumps (relative to current call frame)
				JmpT,			// 1: registry index, 2x: instruction index
				JmpF,			// 1: registry index, 2x: instruction index
				
				// constant index versions
				JmpTC,
				JmpFC,

				// relative jumps (relative to current instruction)
				RJmpT,			// 1: registry index, 2xs: instruction offset
				RJmpF,			// 1: registry index, 2xs: instruction offset
				
				// constant index versions
				RJmpTC,
				RJmpFC,

				/* branching */
				Call,		// 1: number of arguments to call with, 2: registry index of start of arguments, 3: function index
				Ret,		// "return" 1: number of returns, 2: registry index of start of return values
				Jmp,		// 1x: instruction index (relative to current stack frame)
				RJmp,		// 1xs: instruction offset (relative to current instruction)
				
				// constant index versions
				JmpC,
				RJmpC,

				/* misc */
				Nop,		// "No operation". Any arguments are ignored
				Print,		// 1: registry index to print the value of
			};

			Instruction();
			Instruction(std::uint64_t val);
			Instruction(Type t, std::uint64_t);
			Instruction(Type t, std::uint32_t, std::uint32_t);
			Instruction(Type t, std::uint16_t, std::uint16_t, std::uint16_t);

			Type type() const;

			// arg<index>_<size bits>
			// where index is left to right
			std::uint64_t arg1_56() const;

			std::uint32_t arg1_24() const;
			std::uint32_t arg2_32() const;

			std::uint16_t arg1_16() const;
			std::uint16_t arg2_16() const;
			std::uint16_t arg3_16() const;

		private:
			std::uint64_t value;
		};

		using Bytecode = std::vector<Instruction>;
	}
}

#endif
