#pragma once

#include "common.h"
#include "Pos.h"
#include "Move.h"

class ChessBoard {
   public:
    ChessBoard(void);
    ~ChessBoard(void);

#pragma region Statics
    // variants
    static const int VARIANT_DEFAULT = 1;
    static const int VARIANT_DUCK = 2;

    // enumeration of game states
    static const int PLAY = 1;
    static const int CHECK = 2;
    static const int INVALID = 3;        // can be used when setting up a new position
    static const int DRAW_MATERIAL = 4;  // no one can win (ie KING against KING)
    static const int DRAW_50 = 5;        // after 25 full moves no hit or pawnmove occured
    static const int MATE = 6;
    static const int STALEMATE = 7;
    static const int DRAW_REPEAT = 8;  // draw by repetition (3 times same board position)

    // array index of data memebers that hold data for either black or white. these must be 0 and 1
    static const int BLACK = 0;
    static const int WHITE = 1;

    // index and representation of the pieces array and values - must be from [0-5].
    static const int PAWN = 0;
    static const int KNIGHT = 1;
    static const int BISHOP = 2;
    static const int ROOK = 3;
    static const int QUEEN = 4;
    static const int KING = 5;
    // not a piece: a field
    static const int FIELD = -1;

    // Evalutation values
    static int ARRVALUATION[64];
    static const int INDEX_VALUATION_DRAW_REPEAT = 6;

    static const int PIECE_VALUES[6];
    static const int VALUATION_MATE = 100000;  // save max int value
    // zero sum based game, so a draw relates to 0
    static const int VALUATION_DRAW = 0;
    // penalty for repeating moves
    static const int VALUATION_DRAW_REPEAT = -10;
    static const int VALUATION_LONE_KING = 6;  // 6*8=48; best value ending = 48
    static const int VALUATION_LONE_KING_BONUS = 150;
    static const int VALUATION_KING_ENDINGS[64];
    static const int VALUATION_KBNK_SCORE[2][64];

    static const BITBOARD CENTER_4x4_SQUARES = 0x00003C3C3C3C0000LL;
    static const BITBOARD CENTER_SQUARES = 0x00003C7E7E3C0000LL;

    static const int VALUATION_CASTLING_POSSIBLE = -60;
    static const int VALUATION_CASTLING_NOT_POSSIBLE = -100;
    static const int VALUATION_CASTLED = 60;

    static const int VALUATION_EARLY_QUEEN = -60;

    static const int VALUATION_ROOK_OPEN_FILE = 20;
    static const int VALUATION_ROOK_SEMI_OPEN_FILE = 20;
    static const int VALUATION_ROOK_7TH_ROW = 20;
    static const int VALUATION_ROOK_SAME_ROW_FILE = 5;
    static const int VALUATION_ROOK_CONNECTED = 30;
    static const int VALUATION_ROOK_MOBILITY = 8;

    static const int VALUATION_KNIGHT_MOBILITY = 5;
    static const int VALUATION_KNIGHT_CENTER = 5;
    static const int VALUATION_KNIGHT_1ST_ROW = -15;

    static const int VALUATION_BISHOP_1ST_ROW = -10;
    static const int VALUATION_SINGLE_BISHOP_PAWN_COLOR = -5;
    static const int VALUATION_BISHOP_PAIR = 20;
    static const int VALUATION_BISHOP_MOBILITY = 7;

    static const int VALUATION_PAWN_DOUBLED = -50;
    static const int VALUATION_PAWN_PASSED = 30;
    static const int VALUATION_PAWN_FILE_NEIGHBOUR = 5;
    static const int VALUATION_PAWN_CONNECTED = 5;
    static const int VALUATION_PAWN_CENTRE = 5;
    static const int VALUATION_PAWN_IN_KING_RANGE = 5;
    static const int VALUATION_PAWN_ROW = 5;
    static const int VALUATION_PAWN_CENTRE_FIRST_ROW = -30;

    // castlings masks
    static const int MASK_AROOK = 1;
    static const int MASK_HROOK = 2;
    static const int MASK_KING = 4;
    static const int MASK_CASTLED = 8;

    // not consequently used - 64 fields on a chess board, 6 pieces
    static const int NUM_FIELDS = 64;
    static const int NUM_PIECES = 6;
    static const int MAX_MOVES = 255;  // maximum number of moves possible from a position - not yet
                                       // above 218 found documented

    // pre-calculated array of 64 bits BITBOARD values for the squares
    static const BITBOARD BITS[64];
    // above array, but ~
    static const BITBOARD NOT_BITS[64];

    // all bits set to one for the rows (index is row)
    static const BITBOARD ROW_BITS[8];
    // same as ROW_BITS but for the files
    static const BITBOARD FILE_BITS[8];

    // "enumeration" integer position values
    static const int a8 = 0, b8 = 1, c8 = 2, d8 = 3, e8 = 4, f8 = 5, g8 = 6, h8 = 7;
    static const int a7 = 8, b7 = 9, c7 = 10, d7 = 11, e7 = 12, f7 = 13, g7 = 14, h7 = 15;
    static const int a6 = 16, b6 = 17, c6 = 18, d6 = 19, e6 = 20, f6 = 21, g6 = 22, h6 = 23;
    static const int a5 = 24, b5 = 25, c5 = 26, d5 = 27, e5 = 28, f5 = 29, g5 = 30, h5 = 31;
    static const int a4 = 32, b4 = 33, c4 = 34, d4 = 35, e4 = 36, f4 = 37, g4 = 38, h4 = 39;
    static const int a3 = 40, b3 = 41, c3 = 42, d3 = 43, e3 = 44, f3 = 45, g3 = 46, h3 = 47;
    static const int a2 = 48, b2 = 49, c2 = 50, d2 = 51, e2 = 52, f2 = 53, g2 = 54, h2 = 55;
    static const int a1 = 56, b1 = 57, c1 = 58, d1 = 59, e1 = 60, f1 = 61, g1 = 62, h1 = 63;

    // BITBOARD position values - bits in bitboard. [2^0-2^63]
    static const BITBOARD A8 = 1L;
    static const BITBOARD B8 = 2LL;
    static const BITBOARD C8 = 4LL;
    static const BITBOARD D8 = 8LL;
    static const BITBOARD E8 = 16LL;
    static const BITBOARD F8 = 32LL;
    static const BITBOARD G8 = 64LL;
    static const BITBOARD H8 = 128LL;
    static const BITBOARD A7 = 256LL;
    static const BITBOARD B7 = 512LL;
    static const BITBOARD C7 = 1024LL;
    static const BITBOARD D7 = 2048LL;
    static const BITBOARD E7 = 4096LL;
    static const BITBOARD F7 = 8192LL;
    static const BITBOARD G7 = 16384LL;
    static const BITBOARD H7 = 32768LL;
    static const BITBOARD A6 = 65536LL;
    static const BITBOARD B6 = 131072LL;
    static const BITBOARD C6 = 262144LL;
    static const BITBOARD D6 = 524288LL;
    static const BITBOARD E6 = 1048576LL;
    static const BITBOARD F6 = 2097152LL;
    static const BITBOARD G6 = 4194304LL;
    static const BITBOARD H6 = 8388608LL;
    static const BITBOARD A5 = 16777216LL;
    static const BITBOARD B5 = 33554432LL;
    static const BITBOARD C5 = 67108864LL;
    static const BITBOARD D5 = 134217728LL;
    static const BITBOARD E5 = 268435456LL;
    static const BITBOARD F5 = 536870912LL;
    static const BITBOARD G5 = 1073741824LL;
    static const BITBOARD H5 = 2147483648LL;
    static const BITBOARD A4 = 4294967296LL;
    static const BITBOARD B4 = 8589934592LL;
    static const BITBOARD C4 = 17179869184LL;
    static const BITBOARD D4 = 34359738368LL;
    static const BITBOARD E4 = 68719476736LL;
    static const BITBOARD F4 = 137438953472LL;
    static const BITBOARD G4 = 274877906944LL;
    static const BITBOARD H4 = 549755813888LL;
    static const BITBOARD A3 = 1099511627776LL;
    static const BITBOARD B3 = 2199023255552LL;
    static const BITBOARD C3 = 4398046511104LL;
    static const BITBOARD D3 = 8796093022208LL;
    static const BITBOARD E3 = 17592186044416LL;
    static const BITBOARD F3 = 35184372088832LL;
    static const BITBOARD G3 = 70368744177664LL;
    static const BITBOARD H3 = 140737488355328LL;
    static const BITBOARD A2 = 281474976710656LL;
    static const BITBOARD B2 = 562949953421312LL;
    static const BITBOARD C2 = 1125899906842624LL;
    static const BITBOARD D2 = 2251799813685248LL;
    static const BITBOARD E2 = 4503599627370496LL;
    static const BITBOARD F2 = 9007199254740992LL;
    static const BITBOARD G2 = 18014398509481984LL;
    static const BITBOARD H2 = 36028797018963968LL;
    static const BITBOARD A1 = 72057594037927936LL;
    static const BITBOARD B1 = 144115188075855872LL;
    static const BITBOARD C1 = 288230376151711744LL;
    static const BITBOARD D1 = 576460752303423488LL;
    static const BITBOARD E1 = 1152921504606846976LL;
    static const BITBOARD F1 = 2305843009213693952LL;
    static const BITBOARD G1 = 4611686018427387904LL;
    static const BITBOARD H1 = -9223372036854775808ULL;

    // BITS for white and black fields - used to see if a bishop standing on ("is") black or white
    static const BITBOARD WHITE_SQUARES = 0x55AA55AA55AA55AALL;
    static const BITBOARD BLACK_SQUARES = 0xAA55AA55AA55AA55LL;

    // shift, rotation and mask arrays. index is position

    // shifts on non rotated bitboard, used for rank move generation
    static const int SHIFT_0[64];

    // "rotation" table, for the 45 degrees diagonal move generation
    static const int ROT_45[64];
    // same as above, but with BIT positions
    static const BITBOARD ROT_45_BITS[64];
    // the shifts used on the 45 bitb
    static const int SHIFT_45[64];
    // the masks used on the 45 bitb
    static const int MASK_45[64];

    // "rotation" table for file move generation
    // static const int ROT_90[64];
    static const BITBOARD ROT_90_BITS[64];
    static const int SHIFT_90[64];
    // static const int ROT_315[64];
    static const BITBOARD ROT_315_BITS[64];
    static const int SHIFT_315[64];
    static const int MASK_315[64];

    // instead of calling a method row(pos), position is index on array for the rows
    static const int ROW[64];
    // as with ROW, but for column
    static const int COL[64];
    // the distance between to positions
    static int DISTANCE[64][64];
    // the distance between to positions when only vertical and horizontal moves are used
    static int HOOK_DISTANCE[64][64];

    // indexed by position and the 8 bits from the shifted and masked bitboards
    static BITBOARD RANK_MOVES[64][256];
    static BITBOARD DIAG_45_MOVES[64][256];
    static BITBOARD FILE_MOVES[64][256];
    static BITBOARD DIAG_315_MOVES[64][256];

    // bitb arrays, indexed on position. contains the the bit positions that can be reached from
    // that position
    static const BITBOARD BISHOP_RANGE[64];
    static const BITBOARD ROOK_RANGE[64];
    static const BITBOARD QUEEN_RANGE[64];
    static const BITBOARD KNIGHT_RANGE[64];
    static const BITBOARD KING_RANGE[64];
    static BITBOARD PAWN_RANGE[2][64];

    static const int ROW_TURN[2][64];

    static BITBOARD PASSED_PAWN_MASK[2][64];

    // arrays for hashes that will be used to generate hashKey of a board position.
    static BITBOARD HASH_KEY[2][NUM_PIECES][64];
    static BITBOARD HASH_OO[2];
    static BITBOARD HASH_OOO[2];
    static BITBOARD HASH_TURN;

    // default starting column positions for the rooks - these are changed for random Fischer chess.
    static int COL_AROOK;
    static int COL_HROOK;

    // trailing zeros precalculated on 8bit numbers
    static const char TRAILING_ZEROS_8_BITS[256];
    // filled by instantiation of a Game object
    static char TRAILING_ZEROS_16_BITS[65536];
    // precalculated bitcounts
    static char BIT_COUNT_16_BITS[65536];
    static BITBOARD HASH_KEYS[773];
    static const size_t SIZEOF_BOARD;

    static void initStatics();
    static void initValuation();
    static void initBitCount();
    static void initDistance();
    static void initHashKeys();
    static void initMoveArrays();
    static void initTrailingZeros();
    static void initPassedPawnMask();
    static void initPawnRange();

    static void bitbToString(const BITBOARD bb, char* buf);
    static void pieceToString(const int p, char* buf);

#pragma endregion

    inline int trailingZeros(const BITBOARD bb);
    // number of bits in bitb @bb
    inline int bitCount(const BITBOARD bb);

    void printB(char* buf);
    void printMoves(char* buf);

    void reset();
    void commitBoard();
    void duplicate(ChessBoard* ret);
    ChessBoard* getFirstBoard();

    BITBOARD knightAttacks(const int turn, BITBOARD bb);
    BITBOARD bishopAttacks(const int turn, BITBOARD bb);
    BITBOARD rookAttacks(const int turn, BITBOARD bb);
    BITBOARD queenAttacks(const int turn, BITBOARD bb);
    BITBOARD kingAttacks(const int turn, BITBOARD bb);
    boolean isSquareAttacked(const int turn, const int pos);
    void calcState(ChessBoard* board);
    boolean checkInCheck();
    boolean checkInSelfCheck();
    int getState();
    int getVariant();
    void setVariant(int variant);
    boolean isLegalPosition();
    boolean areKingsOnTheBoard();
    boolean isEnded();
    boolean checkEnded();
    int ambigiousMove();
    boolean requestMove(const int from, const int to, ChessBoard* board, ChessBoard* tmpBoard, int promoPiece);
    boolean isAmbiguousCastle(const int from, const int to);
    int getCastleMove(const int from, const int to);
    boolean requestMove(const int m, ChessBoard* board, ChessBoard* tmpBoard);
    boolean requestDuckMove(int newDuckPos);
    void makeMove(const int move, ChessBoard* ret);
    boolean containsQuiescenceMove();
    void addMoves(const int from, BITBOARD bb);
    void addKingMove(const int move);
    void addPawnCaptureMove(const int move);
    void addMove(const int from, const int to);
    int getMyMove();
    void genMoves();
    void genPawnMoves();
    BITBOARD knightMoves(const int turn, const int pos);
    void genKnightMoves();
    BITBOARD rookMoves(const int turn, const int pos);
    void genRookMoves();
    BITBOARD bishopMoves(const int turn, const int pos);
    void genBishopMoves();
    BITBOARD queenMoves(const int turn, const int pos);
    void genQueenMoves();
    BITBOARD kingMoves(const int turn, const int pos);
    void genKingMoves();
    void genExtraKingMoves(const int pos);
    void getMoves();
    void getScoredMoves();
    int getNextScoredMove();
    void scoreMoves();
    void scoreMovesPV(const int move);
    void getScoredMovesTT(const int ttMove, const int killerMove, const int killerMove2);
    int scoreMove(int move);
    void setMyMoveCheck();
    void getPGNMoves(ChessBoard* board, char* sz);
    int boardValue();
    int loneKingValue(const int turn);
    int kbnkValue(const int turn);
    int promotePawns(const int turn);
    int pawnValueExtension(const int turn);
    int kingValueExtension(const int turn);
    inline int queenValueExtension(const int turn);
    int knightValueExtension(const int turn);
    int bishopValueExtension(const int turn);
    int rookValueExtension(const int turn);
    int getAvailableCol(int colNum);
    void toFEN(char* s);
    void toFENBoard(char* s);
    boolean parseFEN(char* sFEN);
    void setCastlingsEPAnd50(boolean wccl, boolean wccs, boolean bccl, boolean bccs, int ep, int r50);
    void setTurn(const int turn);
    int getNumCaptured(int turn, int piece);
    int getNumBoard();
    BITBOARD getHashKey();
    int countPieces();
    int getNoHitCount();
    int getTurn();
    void switchTurn();
    int opponentTurn();
    boolean isPieceOfTurnAt(const int p);
    int getEP();
    boolean hasOO(const int t);
    boolean hasOOO(const int t);
    BITBOARD bitbPositions();
    BITBOARD bitbOpponentPositions();
    BITBOARD bitb();
    BITBOARD bitbAttacked();
    BITBOARD bitbTurnPiece(const int t, const int p);
    inline boolean isPosFree(const int p);
    boolean isPosFriend(const int p);
    boolean isPosEnemy(const int p);
    int pieceAt(const int t, const int p);
    boolean isPieceOfColorAt(const int t, const int p);
    boolean isFieldAt(const int p);
    int getDuckPos();
    boolean getMyDuckPos();
    int getIndex(const int col, const int row);

    void initHashKey();
    void put(const int pos, const int piece, const int turn);
    boolean putHouse(const int pos,
                     const int piece,
                     ChessBoard* nextBoard,
                     ChessBoard* tmpBoard,
                     const boolean allowAttack);
    void remove(const int t, const int p);
    void putDuck(const int duckPos);
    void unsetDuckPos();

    ChessBoard* undoMove();
    boolean hasMoreMoves();
    int getNextMove();
    int getMoveAt(const int i);
    int getNumMoves();
    void removeMoveElementAt();
    void addMoveElement(const int move);
    int remainingMoves();
    void myMoveToString(char* s);
    void calcQuality();

   protected:
    // size 2 for BLACK = 0 and WHITE = 1
    BITBOARD m_bitbPieces[2][NUM_PIECES];
    BITBOARD m_bitbPositions[2];
    // bitb of all pieces
    BITBOARD m_bitb;
    // bitb for diagonal move generation 45 degrees
    BITBOARD m_bitb_45;
    // bitb for file move generation 90
    BITBOARD m_bitb_90;
    // and diagonal 315
    BITBOARD m_bitb_315;
    // bitb with all attacked fields set to 1
    BITBOARD m_bitbAttackMoveSquares;

    // variant of the game - one of the variant constants
    int m_variant;

    // en passant position. -1 if not set
    int m_ep;
    // who's turn is it - BLACK or WHITE
    int m_turn;
    // oppsite of m_turn
    int m_o_turn;
    // kings position (of turn)
    int m_kingPositions[2];
    // state of the game - one of the states constants
    int m_state;
    // administration of number of moves for "no hits rule" - when a board result from a hit or a
    // pawn move, the count is reset to 0.
    int m_50RuleCount;
    // hashKey of this board
    BITBOARD m_hashKey;
    // for each turn an int that holds bitmask of move of "short rook", king and "long rook".
    int m_castlings[2];

    // the array of possible moves
    int m_arrMoves[MAX_MOVES];
    // size of the array
    int m_sizeMoves;
    // current index of move
    int m_indexMoves;

    // sequence number of the bord
    int m_numBoard;
    // parent bord (contains previous position)
    ChessBoard* m_parent;
    // the move that resulted in this board. for the first board 0
    int m_myMove;
    // position of the duck (VARIANT_DUCK)
    int m_duckPos;

    // to keep track of the material quality of self and opponent
    int m_qualities[2];

    // array that is re-used as a temporary array for scoring the moves
    int m_arrScoreMoves[MAX_MOVES];
};
