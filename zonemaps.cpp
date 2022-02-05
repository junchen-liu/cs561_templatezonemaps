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
void zonemap<T>::build(){
    for (int i = 0; i < elements.size(); i++) {
        if (i % num_elements_per_zone == 0){
            //init the zone
            zone<T> curr_zone = zone<T>();;
            curr_zone.max = elements[i];
            curr_zone.min = elements[i];
            curr_zone.elements = std::vector<T>();
            zones.push_back(curr_zone);
        }
        zone<T> curr_zone = zones[i/num_elements_per_zone];
        curr_zone.elements.push_back(elements[i]);
        if(elements[i] > curr_zone.max){
            curr_zone.max = elements[i];
        } else if(elements[i] < curr_zone.min){
            curr_zone.min = elements[i];
        }
    }
}

template<typename T>
bool zonemap<T>::query(T key){
    for (int i = 0; i < zones.size(); i++){
        if(key <= zones[i].max && key >= zones[i].min){
            //Search for the elements
            for(int j = 0; j < zones[i].elements.size(); j++){
                if(zones[i].elements[j] == key){
                    return true;
                }
            }
        }
    }
    return false;//not find, return false
}

template<typename T>
std::vector<T> zonemap<T>::query(T low, T high) {
    std::vector<T> result;
    for(int i = 0; i < zones.size(); i++) {
        if(low > zones[i].max || high < zones[i].min){
            continue;
        }
        for(int j = 0; j < zones[i].elements.size(); j++){
            if(zones[i].elements[j] >= low && zones[i].elements[j] <= high){
                result.push_back(zones[i].elements[j]);
            }
        }
    }
    return result;

}
