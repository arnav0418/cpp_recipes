#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

enum class VehicleType {
    CAR,
    TRUCK,
    MOTORCYCLE
};
enum class SpotType {
    SMALL,
    LARGE,
    MEDIUM
};
enum class TicketStatus {
    ACTIVE,
    PAID
};

int ticketIdCounter = 0;

struct Ticket
{
    int id;
    string vehicleNumber;
    VehicleType vehicleType;
    SpotType spotType;
    TicketStatus status;
    time_t entryTime;
    time_t exitTime;
    double amount;

    Ticket(string vehicleNumber, VehicleType vehicleType, SpotType spotType)
    {
        this->id = ++ticketIdCounter;
        this->vehicleNumber = vehicleNumber;
        this->vehicleType = vehicleType;
        this->spotType = spotType;
        this->status = TicketStatus::ACTIVE;
        this->entryTime = time(nullptr);
        this->exitTime = 0; // Not set until exit
        this->amount = 0.0; // Not set until exit
    }

    void billing(time_t exitTime, double ratePerHour)
    {
        if(status == TicketStatus::PAID) throw runtime_error("Ticket already paid");

        this->exitTime = exitTime;
        long minutes = difftime(exitTime, entryTime) / 60; // Convert seconds to minutes
        long hours = max(1L, (minutes + 59) / 60); // Round up to the nearest hour
        this->amount = hours * ratePerHour;
        this->status = TicketStatus::PAID;

    }

};

class ParkingLot
{
    int smallFree;
    int largeFree;
    int mediumFree;
    map<int, Ticket> tickets; // Maps ticket ID to Ticket object

    double smallRate;
    double largeRate;
    double mediumRate;

    public:

    ParkingLot(int smallSpots, int largeSpots, int mediumSpots)
    {
        this->smallFree = smallSpots;
        this->largeFree = largeSpots;
        this->mediumFree = mediumSpots;
    }

    void setRates(double smallRate, double largeRate, double mediumRate)
    {
        // Set rates for different spot types
        // This could be implemented as a map or similar structure if needed

        this->smallRate = smallRate;
        this->largeRate = largeRate;
        this->mediumRate = mediumRate;
    }

    int parkVehicle(string vehicleNumber, VehicleType vehicleType)
    {
        SpotType spotType = getSpotType(vehicleType);

        if(hasFree(spotType) == false) throw runtime_error("No free parking spots available for this vehicle type");

        decrement(spotType);

        Ticket ticket(vehicleNumber, vehicleType, spotType);
        tickets.emplace(ticket.id, ticket);

        return ticket.id;
    }

    double exitVehicle(int ticketId)
    {
        auto it = tickets.find(ticketId);
        if(it == tickets.end()) throw runtime_error("Invalid ticket ID");

        Ticket& ticket = it->second;

        if(ticket.status == TicketStatus::PAID) throw runtime_error("Ticket already paid");

        time_t exitTime = time(nullptr);
        double ratePerHour = rateFor(ticket.spotType);
        ticket.billing(exitTime, ratePerHour);

        increment(ticket.spotType); // Increment the free spot count

        // Remove the ticket from the map
        tickets.erase(it);

        return ticket.amount;
    }

    private:

    SpotType getSpotType(VehicleType vehicleType)
    {
        switch(vehicleType)
        {
            case VehicleType::CAR:
                return SpotType::MEDIUM;

            case VehicleType::TRUCK:
                return SpotType::LARGE; 

            case VehicleType::MOTORCYCLE:
                return SpotType::SMALL;

            default:
                throw runtime_error("Invalid vehicle type");
                return SpotType::MEDIUM; // Default return to satisfy all control paths
        }
    }

    bool hasFree(SpotType spotType)
    {
        switch(spotType)
        {
            case SpotType::SMALL:
                return smallFree > 0;

            case SpotType::LARGE:
                return largeFree > 0;

            case SpotType::MEDIUM:
                return mediumFree > 0;
            
            default:
                throw runtime_error("Invalid spot type");
                return false; // Default return to satisfy all control paths
        }
    }

    void decrement(SpotType spotType)
    {
        switch(spotType)
        {
            case SpotType::SMALL:
                smallFree--;
                break;
            
            case SpotType::LARGE:
                largeFree--;
                break;
            
            case SpotType::MEDIUM:
                mediumFree--;
                break;
        }
    }

    void increment(SpotType spotType)
    {
        switch(spotType)
        {
            case SpotType::SMALL:
                smallFree++;
                break;
            
            case SpotType::LARGE:
                largeFree++;
                break;
            
            case SpotType::MEDIUM:
                mediumFree++;
                break;
        }
    }

    double rateFor(SpotType spotType)
    {
        switch(spotType)
        {
            case SpotType::SMALL:
                return smallRate;
            
            case SpotType::LARGE:
                return largeRate;
            
            case SpotType::MEDIUM:
                return mediumRate;
            
            default:
                throw runtime_error("Invalid spot type");
                return 0.0; // Default return to satisfy all control paths
        }
        
    }
};

int main()
{
    ParkingLot parkingLot(10, 5, 15); // 10 small, 5 large, 15 medium spots
    parkingLot.setRates(2.0, 5.0, 3.0); // Set rates for small, large, and medium spots

    int t1 = parkingLot.parkVehicle("ABC123", VehicleType::CAR); // Should return ticket ID
    int t2 =  parkingLot.parkVehicle("XYZ456", VehicleType::TRUCK);

    cout<<"Amount: "<< parkingLot.exitVehicle(t1) << endl; // Should return amount for CAR
    cout << "Amount: " << parkingLot.exitVehicle(t2) << endl; // Should return amount for TRUCK

    return 0;


}
