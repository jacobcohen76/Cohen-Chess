all:
	g++                               \
		src/main.cpp                  \
		src/engine/board.cc           \
		src/engine/move_generation.cc \
		src/hash/zobrist.cc           \
		src/io/ascii_board.cc         \
		src/io/cecp.cc                \
		src/io/fen.cc                 \
		src/io/pgn.cc                 \
		src/io/uci.cc                 \
		src/types/bitboard.cc         \
		src/types/direction.cc        \
		src/util/bit_util.cc          \
		src/util/initializer.cc       \
		src/util/random.cc            \
		src/util/string_util.cc