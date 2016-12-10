#include "trackgenerator.h"

TrackGenerator::TrackGenerator()
{}

int TrackGenerator::randNum() {
    return rand() % 3;
}


void TrackGenerator::addLeftCurve() {
    // Actually ADD the curve, +1 on pieces[2], +1 curvesIndicator, +1 piecesCounter
    pieces.push_back(2);
    piecesCounter +=1;
    curvesIndicator +=1;
    allPieces.push_back(2);
}

void TrackGenerator::addRightCurve() {
    // Actually ADD the curve, +1 on pieces[1], -1 rightAngle, +1 piecesCounter
    pieces.push_back(1);
    piecesCounter +=1;
    curvesIndicator -=1;
    allPieces.push_back(1);

}

void TrackGenerator::addStraight() {
    // Actually ADD the piece, +1 on pieces[0], +1 piecesCounter
    if (abs(curvesIndicator)!= 3) {
        straights.push_back(curvesIndicator+3);
    } else {
        straights.push_back(0);
    }

    piecesCounter +=1;
    allPieces.push_back(0);

}


void TrackGenerator::addPiece(int n) {
    switch (n) {
        case 0:
            addStraight();
            std::cout << " 0";
            break;
        case 1:
            addLeftCurve();
            addIndex();
            std::cout << " 2";
            break;
        default:
            addRightCurve();
            addIndex();
            std::cout << " 1";
            break;
    }
}


void TrackGenerator::randomPiece(){
//    double randomDouble = ((double) rand() / (RAND_MAX)) +1;
//    if (randomDouble <= 0.5){
//        addPiece(0);
//    } else {
//        addPiece((rand()%2)+1);
//    }
}



vector<char> & TrackGenerator::generateCircuit(int nOfPieces) {
    srand((unsigned)time(NULL));
    unsigned int nOfPiecesHalf = ceil(nOfPieces/2);


    for (int i=0; i < nOfPiecesHalf; i++) {
        // First half circuit
        if ( nOfPiecesHalf - piecesCounter <= 3 && abs(curvesIndicator)+nOfPiecesHalf - piecesCounter == 3 ) { // nOfPiecesHalf == piecesCounter - (abs(curvesIndicator)-3) && (abs(curvesIndicator)-3) != 0 ) /* Remaining pieces must do 180° curve */ {
            // aggiungi curva per completare 180° angolo
            if (curvesIndicator < 0) addPiece(2);
            else if (curvesIndicator > 0) addPiece(1);
            else addPiece( ( rand() % 2 ) + 1 ); // Choose between the two curves

        } else if ( abs(curvesIndicator) < 3 ) { // Curve still not 180° ---- Probably fix the above ERR here.
            if ( ( (nOfPiecesHalf - piecesCounter) == 3 || nOfPiecesHalf - piecesCounter == 2) && abs(curvesIndicator) < 3 && curvesIndicator!= 0){
                (curvesIndicator > 0) ? addPiece(rand()%2) : addPiece((rand()%2) -1);
            }
            else addPiece(randNum());

        } else if ( abs(curvesIndicator) == 3) { // Curve is 180°
            if(nOfPiecesHalf - piecesCounter == 1) {
                addPiece(0);
            } else if (curvesIndicator < 0) addPiece(rand()%2);
            else {
                addPiece((rand()%2) -1);
            }
        } else {
            printf("ERROR piecesCounter: %d, curvesIndicator: %d, nOfPiecesHalf: %d", piecesCounter, curvesIndicator, nOfPiecesHalf); // Should never go here
        }
    }

    unsigned int countStraight = 0;

    for (char & straight:straights) {

        int num;
        if(piecesIdxs[straight].size() != 0){
            num = rand() % piecesIdxs[straight].size();
        }else{
            //fix this
//            num = rand() % piecesIdxs[straight].size();
        }

        int x = static_cast<unsigned int> (piecesIdxs[straight][num]);

        int countZeros = 0;
        int i = 0;

        while(i-countZeros<x){
            if(pieces[i]==0) ++countZeros;
            ++i;
        }


        pieces.insert(pieces.begin()+ x + countZeros, 0);

        ++countStraight;
    }

    //    1 0 1 0 1 2 1
    //    1 0 1 1 2 0 1


    //    1 0 2 0 3 2 3
    //    4 0 5 6 5 0 6

    // -2->1
    // -1->2
    // 0->3
    // 1->4
    // 2->5
    // +-3->0

    std::cout << std::endl;

    for (char & i:pieces) {
        switch (i) {
            case 0:
                //ADD Straight
                allPieces.push_back(0);
                std::cout << " 0";
                break;
            case 1:
                //ADD Right
                allPieces.push_back(1);
                std::cout << " 1";
                break;
            default:
                //ADD Left
                allPieces.push_back(2);
                std::cout << " 2";
                break;
        }
    }
    return allPieces;

}




