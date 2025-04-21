module academicbuilding;
using namespace std;

AcademicBldg::AcademicBldg(int posn,const string& name) : Property(posn, name, true), Improvements(0) {
    Cost = Costs.at(name)[0];
}


// returns price to buy academic bldg
int AcademicBldg::calculateCost() {
    auto costs = Costs.at(name);
    return costs[0]; 
}

bool AcademicBldg::hasImprovements() const {
    return Improvements > 0;
}

// returns tuition price based on # improvements
int AcademicBldg::calculateFees() const { 
    auto tuition = TuitionScale.at(name);

    if (hasMonopoly() && (Improvements == 0)) {
        return tuition[0] * 2; // base tuition times 2
    }
    
    return tuition[Improvements]; 
}


int AcademicBldg::getImprovements() const {
    return Improvements;
}

void AcademicBldg::setImprovements(int n) {
    Improvements = n;
}

// names of academic buildings 
const std::unordered_set<std::string> AcademicBldg::Names = {
    "AL", "ML", "ECH", "PAS", "HH", "RCH", "DWE", "CPH", "LHI",
    "BMH", "OPT", "EV1", "EV2", "EV3", "PHYS", "B1", "B2", "EIT",
    "ESC", "C2", "MC", "DC"
};


// format: (Name, (PurchaseCost, ImprovementCost))
const std::map<std::string, std::array<int, 2>> AcademicBldg::Costs = {
    {"AL", {40, 50}}, {"ML",{60, 50}}, {"ECH",{100, 50}}, {"PAS",{100, 50}}, {"HH",{120, 50}},
    {"RCH",{140,100}}, {"DWE",{140,100}}, {"CPH",{160,100}},
    {"LHI",{180,100}}, {"BMH",{180,100}}, {"OPT",{200,100}}, 
    {"EV1",{220, 150}}, {"EV2",{220, 150}}, {"EV3",{240, 150}},
    {"PHYS",{260, 150}}, {"B1",{260, 150}}, {"B2",{280, 150}}, 
    {"EIT",{300,200}}, {"ESC",{300,200}}, {"C2",{320,300}},
    {"MC",{350,200}}, {"DC",{400,200}}
};

// Pairs of strings (location name), and vectors of tuition scale based on num improvements
const std::map<std::string, std::array<int, 6>> AcademicBldg::TuitionScale = {
    {"AL", {2, 10, 30, 90, 160, 250}}, {"ML",{4, 20, 60, 180, 320, 450}}, {"ECH",{6, 30, 90, 270, 400, 550}},
     {"PAS",{6, 30, 90, 270, 400, 550}}, {"HH",{8, 40, 100, 300, 450, 600}}, {"RCH",{10, 50, 150, 450, 625, 750}},
    {"DWE",{10, 50, 150, 450, 625, 750}}, {"CPH",{12, 60, 180, 500, 700, 900}}, {"LHI",{14, 70, 200, 550, 750, 950}},
    {"BMH",{14, 70, 200, 550, 750, 950}}, {"OPT",{16, 80, 220, 600, 800, 1000}}, {"EV1",{18, 90, 250, 700, 875, 1050}},
    {"EV2",{18, 90, 250, 700, 875, 1050}}, {"EV3",{20, 100, 300, 750, 925, 1100}}, {"PHYS",{22, 110, 330, 800, 975, 1150}},
    {"B1",{22, 110, 330, 800, 975, 1150}}, {"B2",{24, 120, 360, 850, 1025, 1200}}, {"EIT",{26, 130, 390, 900, 1100, 1275}},
    {"ESC",{26, 130, 390, 900, 1100, 1275}}, {"C2",{28, 150, 450, 1000, 1200, 1400}}, {"MC",{35, 175, 500, 1100, 1300, 1500}},
     {"DC",{50, 200, 600, 1400, 1700, 2000}}
};
