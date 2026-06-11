#include <iostream>
#include <vector>

struct Regression {
    double intercept;
    double slope;
    double rSquared;
};

// Recursive data total
void sumData(const std::vector<double>& xData, const std::vector<double>& yData, int index, 
             double& totalX, double& totalY, double& totalXY, double& totalX2) {
    if (index >= xData.size()) {
        return;
    }

    double currentX = xData[index];
    double currentY = yData[index];

    totalX  += currentX;
    totalY  += currentY;
    totalXY += currentX * currentY;
    totalX2 += currentX * currentX;

    sumData(xData, yData, index + 1, totalX, totalY, totalXY, totalX2);
}

void buildModel(const std::vector<double>& xData, const std::vector<double>& yData, Regression& outModel) {
    if (xData.size() != yData.size()) {
        return;
    }

    int dataSize = xData.size();
    if (dataSize == 0) return;

    double totalX  = 0.0;
    double totalY  = 0.0;
    double totalXY = 0.0;
    double totalX2 = 0.0;

    sumData(xData, yData, 0, totalX, totalY, totalXY, totalX2);

    double bottomPart = (dataSize * totalX2) - (totalX * totalX);
    if (bottomPart == 0.0) return;

    outModel.slope = ((dataSize * totalXY) - (totalX * totalY)) / bottomPart;
    outModel.intercept = (totalY - (outModel.slope * totalX)) / dataSize;

    // Prediction accuracy
    double meanY = totalY / dataSize;
    double totalError = 0.0;
    double residError = 0.0;

    for (int index = 0; index < dataSize; ++index) {
        double currentX = xData[index];
        double currentY = yData[index];
        double predictY = outModel.intercept + (outModel.slope * currentX);

        totalError += (currentY - meanY) * (currentY - meanY);
        residError += (currentY - predictY) * (currentY - predictY);
    }

    if (totalError == 0.0) {
        outModel.rSquared = 1.0;
    } else {
        outModel.rSquared = 1.0 - (residError / totalError);
    }
}

// Overload single prediction
double makePrediction(double targetX, const Regression& fitModel) {
    return fitModel.intercept + (fitModel.slope * targetX);
}

// Overload recursive prediction
void makePrediction(double startX, double endX, double stepSize, const Regression& fitModel) {
    if (startX > endX) {
        return;
    }
    
    double predictY = makePrediction(startX, fitModel);
    std::cout << "  Input = " << startX << "  =>  Output = " << predictY << "\n";
    
    makePrediction(startX + stepSize, endX, stepSize, fitModel);
}

void printStats(const Regression& fitModel) {
    std::cout << "  Equation : y = " << fitModel.intercept 
              << " + " << fitModel.slope << " * x\n";
    std::cout << "  R-Squared: " << fitModel.rSquared 
              << "\n  PREDICTION ACCURACY: " << fitModel.rSquared * 100 << "%\n";
}

int main() {
    std::cout << "=========================================\n";
    std::cout << "        LINEAR REGRESSION SEADANYA       \n";
    std::cout << "=========================================\n";

    std::cout << "\n[Dataset 1] Study hours vs Test scores\n";
    std::vector<double> hoursData = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<double> scoreData = {40, 50, 55, 60, 70, 75, 85, 90};
    
    Regression modelOne;
    buildModel(hoursData, scoreData, modelOne);
    printStats(modelOne);
    
    std::cout << "\nScore predictions for 1-5 hours:\n";
    makePrediction(1.0, 5.0, 1.0, modelOne);

    std::cout << "\n-----------------------------------------\n";
    std::cout << "[Dataset 2] Temperature (C) vs Power (kWh)\n";
    std::vector<double> tempData  = {20, 22, 25, 28, 30, 33, 35};
    std::vector<double> powerData = {5.0, 5.5, 6.2, 7.1, 7.8, 8.5, 9.0};
    
    Regression modelTwo;
    buildModel(tempData, powerData, modelTwo);
    printStats(modelTwo);

    std::cout << "\nPower predictions for 20-25 degrees:\n";
    makePrediction(20.0, 25.0, 1.0, modelTwo);

    std::cout << "\n=========================================\n";
    return 0;
}