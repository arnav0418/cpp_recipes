#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <stdexcept>
#include <ctime>

using namespace std;

enum class spotType
{
    SMALL,
    MEDIUM,
    LARGE
};

enum class vehicleType
{
    MOTORCYCLE,
    CAR,
    TRUCK
};

enum class ticketStatus
{
    PAID,
    UNPAID
};

static int ticket_id_counter = 0;

struct Ticket
{
    int ticketId;
    vehicleType vehicle;
    spotType spot;
    ticketStatus status;
    string vehicleNumber;
    time_t entry_time;
    time_t exit_time;
    double amount;

    public:

    Ticket(vehicleType vehicle, spotType spot, string vehicleNumber)
    {
        this->ticketId = ++ticket_id_counter;
        this->vehicle = vehicle;
        this->spot = spot;
        this-> status = ticketStatus::UNPAID;
        this->vehicleNumber = vehicleNumber;
        this->entry_time = time(nullptr);
        this->exit_time = 0;
        this->amount = 0.0;
    }

    void billing(double ratePerHour)
    {
        if(status == ticketStatus::PAID) throw runtime_error("Ticket already paid");

        this->exit_time = time(nullptr);
        long long time_diff = difftime(exit_time,entry_time);
        long long minutes = time_diff/60;
        long long hours = max(1LL, (minutes + 59) / 60);
        this->amount = hours*ratePerHour;
        this->status = ticketStatus::PAID;
    }
};

class Parking
{
    int smallFree;
    int mediumFree;
    int largeFree;

    unordered_map<int,Ticket> ticket_register;

    double smallRate;
    double mediumRate;
    double largeRate;

    public:

    Parking(int smallFree, int mediumFree, int largeFree)
    {
        this->smallFree = smallFree;
        this->mediumFree = mediumFree;
        this->largeFree = largeFree;
    }

    void setRate(double smallRate, double mediumRate, double largeRate)
    {
        this->smallRate = smallRate;
        this->mediumRate = mediumRate;
        this->largeRate = largeRate;
    }

    int entry(string vehicleNumber, vehicleType vehicle)
    {
        spotType spot = get_spot_type(vehicle);

        if(!isFree(spot)) throw runtime_error("sorry! lot is full.");

        allocate_spot(spot);

        Ticket ticket(vehicle, spot, vehicleNumber);
        ticket_register.emplace(ticket.ticketId, ticket);

        return ticket.ticketId;
    }

    double exit(int ticketId)
    {
        auto it = ticket_register.find(ticketId);
        if(it == ticket_register.end()) throw runtime_error("Invalid ticket ID");

        Ticket ticket = it->second;
        if(ticket.status == ticketStatus::PAID) throw runtime_error("ticket already paid");

        double rate = rateFor(ticket.spot);
        ticket.billing(rate);

        double amount = ticket.amount;

        deallocate_spot(ticket.spot);

        ticket_register.erase(it);

        return amount;

    }

    private:

    spotType get_spot_type(vehicleType vehicle)
    {
        switch(vehicle)
        {
            case vehicleType::CAR :
                return spotType::MEDIUM;

            case vehicleType::MOTORCYCLE :
                return spotType::SMALL;

            case vehicleType::TRUCK :
                return spotType::LARGE;

            default :
                throw runtime_error("invalid vehicle type");
                return spotType::MEDIUM;

        }
    }

    bool isFree(spotType spot)
    {
        switch(spot)
        {
            case spotType::LARGE :
                return (largeFree > 0);
            
            case spotType::SMALL :
                return (smallFree > 0);

            case spotType::MEDIUM :
                return (mediumFree > 0);

            default :
                return false;
        }
    }

    void allocate_spot(spotType spot)
    {
        switch(spot)
        {
            case spotType::LARGE :
                largeFree--;
                break;
            
            case spotType::SMALL :
                smallFree--;
                break;

            case spotType::MEDIUM :
                mediumFree--;
                break;

            default :
                throw runtime_error("invalid spot type");
        }
    }

    void deallocate_spot(spotType spot)
    {
        switch(spot)
        {
            case spotType::LARGE :
                largeFree++;
                break;
            
            case spotType::SMALL :
                smallFree++;
                break;

            case spotType::MEDIUM :
                mediumFree++;
                break;

            default :
                throw runtime_error("invalid spot type");
        }
    }


    double rateFor(spotType spotType)
    {
        switch(spotType)
        {
            case spotType::SMALL:
                return smallRate;
            
            case spotType::LARGE:
                return largeRate;
            
            case spotType::MEDIUM:
                return mediumRate;
            
            default:
                throw runtime_error("Invalid spot type");
                return 0.0; // Default return to satisfy all control paths
        }
        
    }
    
};

int main()
{
    Parking parkingLot(10, 5, 15); 
    parkingLot.setRate(2.0, 5.0, 3.0); 

    int t1 = parkingLot.entry("ABC123", vehicleType::CAR); // Should return ticket ID
    int t2 =  parkingLot.entry("XYZ456", vehicleType::TRUCK);

    cout<<"Amount: "<< parkingLot.exit(t1) << endl; // Should return amount for CAR
    cout << "Amount: " << parkingLot.exit(t2) << endl; // Should return amount for TRUCK

    return 0;

}