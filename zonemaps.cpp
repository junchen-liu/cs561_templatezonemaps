#include "zonemaps.h"

template<typename T>
zonemap<T>::zonemap(std::vector<T> _elements, uint _num_elements_per_zone)
{
    elements = _elements;
    num_elements_per_zone = _num_elements_per_zone;
    zones = std::vector<zone<T>>();
    num_zones = 0;
}

template<typename T>
bool zonemap<T>::query(T key)
{
    return false;
}

template<typename T>
void zonemap<T>::build(){
    for (int i = 0; i < elements.size(); i++) {
        if (i % num_elements_per_zone == 0){
            //init the zone
            zone<T> zone = zone<T>();
            zone.max = elements[i];
            zone.min = elements[i];
            zone.elements = std::vector<<T>();
            zones.push_back(zone);
        }
        zone<T> curr_zone = zones[i/num_elements_per_zone];
        curr_zone.elements.push_back(elements[i])
        if(elements[i] > curr_zone.max){
            curr_zone.max = elements[i];
        } else if(elements[i] < curr_zone.min){
            curr_zone.min = elements[i];
        }
    }
}
