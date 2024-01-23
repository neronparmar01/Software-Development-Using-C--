// Workshop 2 - Summer 2023
// w2_p1.cpp
// Rania Arbash
// Name : Neron Parmar
// Date : 9/22/23
// File : w2_p1.cpp
// All of the coding done is my work and no work of mine is shared to anyone or on any page

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "AirportModels.h"

using namespace std;
namespace sdds {

    // Airport class implementation

    Airport::Airport() {
        code = "";
        name = "";
        city = "";
        state = "";
        country = "";
        latitude = 0.0;
        longitude = 0.0;
    }

    Airport::Airport(const std::string& code, const std::string& name, const std::string& city, const std::string& state, const std::string& country, double latitude, double longitude) {
        this->code = code;
        this->name = name;
        this->city = city;
        this->state = state;
        this->country = country;
        this->latitude = latitude;
        this->longitude = longitude;
    }

    bool Airport::isEmpty() const {
        return code.empty() || name.empty() || city.empty() || state.empty() || country.empty();
    }

    std::ostream& operator<<(std::ostream& os, const Airport& airport) {

        if (airport.isEmpty()) {
            os << "Empty Airport";
        }
        else {
            os.fill('.');
            os.setf(std::ios::right);
            os.width(20);
            os << "Airport Code"
                << " : ";
            os.unsetf(std::ios::right);
            os.setf(std::ios::left);
            os.width(30);
            os << airport.code << std::endl;
            os.unsetf(std::ios::left);

            os.setf(std::ios::right);
            os.width(20);
            os << "Airport Name"
                << " : ";
            os.unsetf(std::ios::right);
            os.setf(std::ios::left);
            os.width(30);
            os << airport.name << std::endl;
            os.unsetf(std::ios::left);

            os.setf(std::ios::right);
            os.width(20);
            os << "City"
                << " : ";
            os.unsetf(std::ios::right);
            os.setf(std::ios::left);
            os.width(30);
            os << airport.city << std::endl;
            os.unsetf(std::ios::left);

            os.setf(std::ios::right);
            os.width(20);
            os << "State"
                << " : ";
            os.unsetf(std::ios::right);
            os.setf(std::ios::left);
            os.width(30);
            os << airport.state << std::endl;
            os.unsetf(std::ios::left);

            os.setf(std::ios::right);
            os.width(20);
            os << "Country"
                << " : ";
            os.unsetf(std::ios::right);
            os.setf(std::ios::left);
            os.width(30);
            os << airport.country << std::endl;
            os.unsetf(std::ios::left);

            os.setf(std::ios::right);
            os.width(20);
            os << "Latitude"
                << " : ";
            os.unsetf(std::ios::right);
            os.setf(std::ios::left);
            os.width(30);
            os << airport.latitude << std::endl;
            os.unsetf(std::ios::left);

            os.setf(std::ios::right);
            os.width(20);
            os << "Longitude"
                << " : ";
            os.unsetf(std::ios::right);
            os.setf(std::ios::left);
            os.width(30);
            os << airport.longitude << std::endl;
            os.unsetf(std::ios::left);
        }
        return os;
    }


    // AirportLog implemetation
    AirportLog::AirportLog() {
        airports = nullptr;
        count = 0;
    }

    AirportLog::AirportLog(const char* filename): airports(nullptr), count(0){
     
        std::ifstream file(filename);
        std::string lines;

        if (!file.is_open()) {
            cerr << "Empty Airport" << endl;
            return;
       }

        getline(file, lines);

        while (getline(file, lines)) {
            count++;
        }

        airports = new Airport[count];
        
        file.clear();
        file.seekg(0);
        std::getline(file, lines);

        for (size_t i = 0; i < count; i++) {
            std::getline(file, airports[i].code, ',');
            std::getline(file, airports[i].name, ',');
            std::getline(file, airports[i].city, ',');
            std::getline(file, airports[i].state, ',');
            std::getline(file, airports[i].country, ',');
            file >> airports[i].latitude;
            file.ignore(); 
            file >> airports[i].longitude;
            file.ignore(); // Ignores the newline character
        }

        file.close();
    }

    AirportLog::~AirportLog() {
        delete[] airports;
        airports = nullptr;
    }

    void AirportLog::addAirport(const Airport& airport) {
        Airport* temp;
        temp = new Airport[count];
        for (size_t i = 0; i < count; i++) {
            temp[i] = airports[i];
        }
        delete[] airports;
        airports = new Airport[count + 1];
        for (size_t i = 0; i < count; i++) {
            airports[i] = temp[i];
        }
        airports[count] = airport;
        count++;
        delete[]temp;
        temp = nullptr;
    }


    AirportLog AirportLog::findAirport(const char* state, const char* country) const {
        AirportLog result;
        for (size_t i = 0; i < count; i++) {
            if (airports[i].state ==  state && airports[i].country == country) {
                result.addAirport(airports[i]);
            }
        }
        return result;
    }

    Airport AirportLog::operator[](size_t idx) const {
        Airport AirPort;
        if (idx < count) {
            return airports[idx];
        }
        return AirPort;
    }

    AirportLog::operator size_t() const {
        return count;
    }
} // namespace sdds
