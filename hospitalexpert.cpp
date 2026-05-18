#include <iostream>
#include <string>

using namespace std;

bool askQuestion(std::string question) {
    std::string answer;
    std::cout << question << " (yes/no): ";
    std::cin >> answer;
    return (answer == "yes" || answer == "y");
}

int main() {
    std::cout << "--- Medical Diagnosis Expert System ---" << std::endl;

    bool fever = askQuestion("Do you have a fever?");
    bool cough = askQuestion("Do you have a persistent cough?");
    bool headache = askQuestion("Do you have a severe headache?");
    bool body_ache = askQuestion("Do you experience muscle or body aches?");
    bool sore_throat = askQuestion("Do you have a sore throat?");

    std::cout << "\n--- System Diagnosis ---" << std::endl;

    if (fever && cough && body_ache && sore_throat) {
        std::cout << "Result: You might have the Flu (Influenza)." << std::endl;
        std::cout << "Recommendation: Rest, stay hydrated, and consult a doctor if symptoms worsen." << std::endl;
    } 
    else if (fever && cough && !body_ache && sore_throat) {
        std::cout << "Result: You might have a Common Cold." << std::endl;
        std::cout << "Recommendation: Get plenty of rest and take over-the-counter cold medications." << std::endl;
    } 
    else if (fever && headache && body_ache) {
        std::cout << "Result: You might have a Viral Fever or Dengue." << std::endl;
        std::cout << "Recommendation: Visit a hospital immediately for a blood test." << std::endl;
    } 
    else if (!fever && cough && sore_throat) {
        std::cout << "Result: You might have a Throat Infection or Allergies." << std::endl;
        std::cout << "Recommendation: Try warm saltwater gargles and avoid cold beverages." << std::endl;
    } 
    else if (headache && !fever && !cough) {
        std::cout << "Result: You might be experiencing Tension Headaches or Dehydration." << std::endl;
        std::cout << "Recommendation: Drink water, reduce screen time, and get adequate sleep." << std::endl;
    } 
    else {
        std::cout << "Result: Symptoms are unclear or do not match common profiles." << std::endl;
        std::cout << "Recommendation: Please consult a medical professional for an accurate clinical diagnosis." << std::endl;
    }

    return 0;
}
