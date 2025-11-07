#include <iostream>
#include <memory>
#include "include/Point.h"
#include "include/Figure.h"
#include "include/Rhombus.h"
#include "include/Trapezoid.h"
#include "include/Pentagon.h"
#include "include/Array.h"

int main() {
    Array<Figure<double>> figures;

    std::cout << "1. Adding figures to the array...\n";
    figures.push_back(std::make_shared<Rhombus<double>>(
        Point<double>(0, 0),
        Point<double>(2, 0),
        Point<double>(1, 1.732),
        Point<double>(-1, 1.732)
    ));
    figures.push_back(std::make_shared<Trapezoid<double>>(
        Point<double>(0, 0),
        Point<double>(4, 0),
        Point<double>(3, 2),
        Point<double>(1, 2)
    ));
    figures.push_back(std::make_shared<Pentagon<double>>(
        Point<double>(1, 0),
        Point<double>(0.309, 0.951),
        Point<double>(-0.809, 0.588),
        Point<double>(-0.809, -0.588),
        Point<double>(0.309, -0.951)
    ));

    std::cout << "   Added " << figures.getSize() << " figures. Capacity: " << figures.getCapacity() << "\n\n";

    std::cout << "2. Figure details:\n";
    double total_area = 0.0;

    for (size_t i = 0; i < figures.getSize(); ++i) {
        const auto& fig = figures[i];
        std::cout << "   [" << i << "] Type: ";
        if (dynamic_cast<const Rhombus<double>*>(&fig)) std::cout << "Rhombus";
        else if (dynamic_cast<const Trapezoid<double>*>(&fig)) std::cout << "Trapezoid";
        else if (dynamic_cast<const Pentagon<double>*>(&fig)) std::cout << "Pentagon";
        else std::cout << "Unknown";

        std::cout << "\n        Center: " << fig.getCenter();
        double area = static_cast<double>(fig);
        std::cout << "\n       Area: " << area;
        std::cout << "\n       Vertices: " << fig << "\n\n";
        total_area += area;
    }
    
    std::cout << "3. Total area of all figures: " << total_area << "\n\n";

    std::cout << "4. Removing the trapezoid (index 1)...\n";
    figures.remove_at(1);
    std::cout << "   Remaining figures: " << figures.getSize() << "\n";

    std::cout << "\n5. Updated figure list:\n";
    for (size_t i = 0; i < figures.getSize(); ++i) {
        const auto& fig = figures[i];
        std::string type = dynamic_cast<const Rhombus<double>*>(&fig) ? "Rhombus" : "Pentagon";
        std::cout << "   [" << i << "] " << type
                  << " Center: " << fig.getCenter()
                  << ", Area: " << static_cast<double>(fig) << "\n";
    }

    std::cout << "\nDemonstration completed successfully.\n";
    return 0;
}