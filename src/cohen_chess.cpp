#include <cohen_chess.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <locale>

const std::string kTestImportPgn =
{
    "[Event \"Madrid\"]\n"
    "[Site \"?\"]\n"
    "[Date \"1547.??.??\"]\n"
    "[Round \"?\"]\n"
    "[White \"Leonardo, Giovanni\"]\n"
    "[Black \"Lopez, Ruy\"]\n"
    "[Result \"1-0\"]\n"
    "[ECO \"C53\"]\n"
    "[Annotator \"JvR\"]\n"
    "[PlyCount \"17\"]\n"
    "[EventDate \"1600.??.??\"]\n"
    "\n"
    "{New annotations were written by Jan van Reek. The quality of his analyses\n"
    "might be surprising, because chess analysis used to be the domain of\n"
    "over-the-board grandmasters. Chess software made it possible for study\n"
    "composers and correspondence players to analyse at a similar level. Scientific\n"
    "ability has become a more important quality.   The selected games were\n"
    "thoroughly investigated with modern means. It took me about one day per game.\n"
    "The oldest games have rarely been analysed previously. I do not bother the\n"
    "reader with endless reports about lack of quality in earlier analyses. Authors\n"
    "of important variations are mentioned.  When a game of chess is finished, the\n"
    "need for another game comes natural. Chess players like to play several games\n"
    "successively. If conditions are set, a match is created. When chess players\n"
    "began to travel as businessman or tourist, international competition started.\n"
    "The documented match came into being, when 'the foreign star' played against\n"
    "'the local hero' and journalists wrote about it. Technical reports were\n"
    "published in the first chess journals. World champions have written about the\n"
    "history of chess. Euwe painted an objective scientific picture of Steinitz'\n"
    "positional play. Fischer wrote with great enthusiasm about players of the\n"
    "nineteenth century. He listed Morphy, Staunton, Steinitz, Tarrasch and Chigorin\n"
    "among the best ten chess players ever and praised their originality.  When\n"
    "modern chess developed, only the rich and mighty had spare time for the game.\n"
    "The first remaining book about the renewed game was published by Lecena in\n"
    "1497. Probably he had just made a Grand Tour in Spain, France and Italy.  \n"
    "Chess remained a pastime for centuries. Few players found the competitive\n"
    "element important. The priest Ruy L�pez visited Rome in 1560. He was the\n"
    "strongest Spanish player and defeated all Italian players. Only the young law\n"
    "student Leonardo offered strong resistance.   Ruy L�pez lived at the court of\n"
    "Philips II. Leonardo, Polerio and Rosces travelled to Madrid in 1574. Boi\n"
    "followed later. The Italians had become stronger than the Spaniards. The first\n"
    "important international chess match, Leonardo - Ruy L�pez, ended in 3-2. Only\n"
    "three openings' fragments have survived. One example has been selected. The\n"
    "king rewarded the winner well.} 1. e4 e5 2. Nf3 Nc6 3. Bc4 Bc5 4. c3 Qe7 5. b4\n"
    "Bb6 6. a4 a6 7. Ba3 d6 8. d3 Bg4 9. Nbd2 {Leonardo's cautious play becomes\n"
    "apparent. He won this game. King Philips II rewarded him well when Ruy L�pez\n"
    "was defeated with 3-2 in the match for three won games. Three opening fragments\n"
    "from the event remained known.} 1-0\n"
    ""
};

const std::string kTestExportPgn =
{
    "[Event \"URS-chT\"]\n"
    "[Site \"URS\"]\n"
    "[Date \"1966.??.??\"]\n"
    "[Round \"?\"]\n"
    "[White \"Bykhovsky, Anatoly A\"]\n"
    "[Black \"Alburt, Lev O\"]\n"
    "[Result \"1-0\"]\n"
    "[WhiteElo \"\"]\n"
    "[BlackElo \"\"]\n"
    "[ECO \"B29\"]\n"
    "\n"
    "1.e4 c5 2...Nf3 Nf6 3.e5 Nd5 4.Nc3 e6 5.Ne4 Qc7 6.b3 Nc6 7.Bb2 Nd4 8.Bc4 Nb4\n"
    "9.O-O Nbxc2 10.Rc1 Qc6 11.Rxc2 Qxe4 12.Nxd4 cxd4 13.Qc1 Bb4 14.Bd3 Qxd3 15.Rxc8+ Ke7\n"
    "16.Rxh8 Rxh8 17.a3 Bxd2 18.Qc5+ Kd8 19.Qxa7 Bc3 20.Qb8+ Ke7 21.Qd6+ Kd8 22.Qb8+ Ke7\n"
    "23.Qd6+ Kd8 24.Bxc3 Qxc3 25.Rd1 f6 26.g3 Qc7 27.Qxd4 fxe5 28.Qg4 Re8 29.Qxg7 d5\n"
    "30.Qg5+ Kd7 31.Rc1 Qb8 32.b4 e4 33.b5 Qd6 34.Qg7+ Re7 35.Qh8 Re8 36.Qg7+ Qe7\n"
    "37.Qc3 Rd8 38.b6 e5 39.Qc7+ Ke8 40.Qxe7+ Kxe7 41.Rc7+ Rd7 42.Rxd7+ Kxd7 43.g4 d4\n"
    "44.h4 Ke6 45.Kf1 Kd5 46.Ke2 Kc4 47.Kd2  1-0"
};

int main(int argc, char* argv[])
{
    std::cout << "Hello World!" << std::endl;

    std::cout << sizeof(cohen_chess::Token<char>) << std:: endl;
    
    cohen_chess::Board board = {};
    cohen_chess::SetFenPosition(cohen_chess::kFenStartingPosition, board);
    std::cout << cohen_chess::AsciiBoard(board) << std::endl;

    std::istringstream pgn_iss;
    cohen_chess::GameLog log;

    std::cout << "Start:" << std::endl;

    log.clear(); 
    pgn_iss = std::istringstream(kTestExportPgn);
    cohen_chess::ParseImportPgn(pgn_iss, log);
    return 0;
}
