export module academicbuilding;
//import <unordered_map>;
import <unordered_set>;
import <vector>;
import <array>;
import <map>;
import <iostream>;
import <string>;
import property;

using namespace std;

export class AcademicBldg : public Property { 
    int Improvements;  //number of improvement 0-5
    public:
    AcademicBldg(int posn, const std::string& name);
    //int calculateFees(); //uses the hardcoded tuition scale map to calculate the tuition
    int calculateCost(); //uses the hardcoded costs map to get the original price of the building
    
    bool hasImprovements() const override; // returns true if has improvements
    int getImprovements() const;
    void setImprovements(int n);
    int calculateFees() const override;

    static const std::unordered_set<std::string> Names;
    static const std::map<std::string, std::array<int, 2>> Costs;
    static const std::map<std::string, std::array<int, 6>> TuitionScale;
};
