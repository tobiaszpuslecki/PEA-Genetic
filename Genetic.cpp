#include "Genetic.hpp"

using namespace std;

Genetic::Genetic()
{
}

// ctor with all needed inits
Genetic::Genetic(const vector<vector<int> >& matrix_)
{
  this->dimension = static_cast<int>(matrix_.size());
  matrix.resize(this->dimension, std::vector<int>(this->dimension));

  for(int i=0; i<this->dimension ; i++)
  {
    for(int j=0; j<this->dimension ; j++)
    {
      matrix[i][j] = matrix_[i][j];
    }
  }
    
    iterations = 1000;
    swapsInMutation = 10;
    
    population.reserve(populationSize);
    parents.reserve(dimension);
}


int Genetic::alghoritm()
{
    // random seed init
    srand((unsigned int)time(NULL));

    // time stop criteria init
    auto internalBeginTime = std::chrono::system_clock::now();
    auto currentTimeInSeconds = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds;
    
        // generate initial population
        generatePopulation();
    
        // make calculations in 0..iterations
        for (int i = 0; i < iterations; ++i)
        {

            // stop criteria implementation
            currentTimeInSeconds = std::chrono::system_clock::now();
            elapsed_seconds = currentTimeInSeconds - internalBeginTime;
            if ( elapsed_seconds.count() > stopCriteria)
            {
                return bestLength;
            }

            // choose paretns for max completion time function
            chooseParents();

            // make cross function with choosen cross method variant
            if (getRandomDouble() < crossFactor)
            {
                cross(crossMethodVariant);
            }
            // generate new population after crossing
            generateNewPopulation();

            //calculate current length using max completion time function
            int currentLength = UINT_MAX - calculateMaxCompletionTime(population.front());
            
            //update if better
            if (currentLength < bestLength)
            {
                foundInTime = static_cast<double>(elapsed_seconds.count());
                bestLength = currentLength;
                bestPath = population.front();
            }
        }
    return bestLength;
}

int Genetic::calculate(int stopCriteria_, int populationSize_, double mutationFactor_, double crossFactor_, int crossMethodVariant_, int mutationMethodVariant_)
{
    // params inits
    stopCriteria = stopCriteria_;
    populationSize = populationSize_;
    mutationFactor = mutationFactor_;
    crossFactor = crossFactor_;

    crossMethodVariant = crossMethodVariant_;
    mutationMethodVariant = mutationMethodVariant_;
    

  this->startTime = std::chrono::system_clock::now();
  int path = alghoritm();
  this->endTime = std::chrono::system_clock::now();
    
    for (int k=0; k<dimension; k++) {
        cout << " " << bestPath[k];
    }
    cout << " " << bestPath[0] << "  " << " | Found in : " << foundInTime << " | ";
    
  return path;
}

double Genetic::getExecutionTime()
{
  std::chrono::duration<double> elapsed_seconds = this->endTime - this->startTime;

  return elapsed_seconds.count();
}

void Genetic::generatePopulation()
{
    // geenrate random population
    for (int i = 0; i < populationSize; i++)
    {
        vector<int> permutation = generateRandomPermutation();
        population.push_back(permutation);
    }
}

vector<int> Genetic::generateRandomPermutation()
{
    // generate random population using std::shuffle and std::default_random_engine
    vector<int> v;
    for (int i=0; i<dimension; i++)
        v.push_back(i);

    shuffle(v.begin(), v.end(), default_random_engine(rand()));
    
    return v;
}

void Genetic::chooseParents()
{
    // roulette method
    // choose paretns for max completion time function
    parents.clear();

    // values inits
    unsigned long long permutationSum = 0;
    vector <int> permutationValues(populationSize);
    unsigned long long currentValue = 0;
    unsigned long long lastValue = 0;

    // calculate sum of all completion time functions (pol. funkcji przystosowania)
    for (int i = 0; i < populationSize; i++)
    {
        permutationValues[i] = calculateMaxCompletionTime(population[i]);
        permutationSum += permutationValues[i];
    }

    // find max completion time function equals random value
    for (int i = 0; i < dimension; i++)
    {
        //generate random value
        unsigned long randomValue = getRandomDouble() * permutationSum;
        // zeroes params
        currentValue = 0;
        lastValue = 0;

        // for i in 0..populationSize
        for (int i = 0; i < populationSize; i++)
        {
            // accumulate permutation values in currentValue
            currentValue += permutationValues[i];

            // if randomValue in <lastValue;currentValue>
            if (randomValue >= lastValue and randomValue <= currentValue)
            {
                // push back population[i] to parents
                parents.push_back(population.at(i));
                break;
            }
            // accumulate permutation values in lastValue
            lastValue += permutationValues[i];
        }
    }
}

double Genetic::getRandomDouble()
{
    // generate random double value
    return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
}

int Genetic::calculateMaxCompletionTime(vector<int> v)
{
    // calculating max completion time functions
    unsigned int sum = 0;
    for (int i = 0; i < dimension - 1; i++)
    {
        // calc sum of paths
        sum += matrix[v[i]][v[i+1]];
    }
    // add last (return) edge
    sum += matrix[v[dimension - 1]] [v[0]];
    // return (inf - sum)
    return (UINT_MAX - sum);
}

void Genetic::cross(int crossMethodVariant)
{
    // cross function with two variants
    vector<int> parent1 = parents.at(rand() % dimension);
    vector<int> parent2 = parents.at(rand() % dimension);

    vector<int> child1(dimension);
    vector<int> child2(dimension);
    
    if(crossMethodVariant==1)
    {
        //first variant PMX
        for (int i = 0; i < dimension; i++)
        {
            // assign parentsX[i] to proper child
            child1[i] = parent1[i];
            child2[i] = parent2[i];
        }
        
        // get random cross points
        int crossPoint1 = rand() % dimension;
        int crossPoint2 = rand() % dimension;

        // cross if first if greater than second make swap
        if (crossPoint1 > crossPoint2)
        {
            swap(crossPoint2, crossPoint1);
        }

        // for crossPoint1..crossPoint2 make swaps
        for (int i = crossPoint1; i <= crossPoint2; ++i)
        {
            swap(child1[i], child2[i]);
        }

        // for crossPoint1..crossPoint2 do child assigns
        for (int i = crossPoint1; i <= crossPoint2; ++i)
        {
            // for crossPoints1 number do
            for (int j = 0; j < crossPoint1; j++)
            {
                // if childs equals then assign
                if (child1[j] == child1[i])
                    child1[j] = child2[i];
                if (child2[j] == child2[i])
                    child2[j] = child1[i];
            }
        }
    }
    else if (crossMethodVariant == 2)
    {
        //second method
        //experimantal
        // get random cross points
        int crossPoint1 = (int) (rand() * parent1.size());
        int crossPoint2 = (int) (rand() * parent1.size());

        // for 0..child1.size make
        for (int i = 0; i < child1.size(); i++)
        {
            // if crossPoints1 is less than crossPoint2, and i is in (crossPoint1;crossPoint2)
            if (crossPoint1 < crossPoint2 and i > crossPoint1 and i < crossPoint2)
            {
                child1[i] = parent1[i];
            }
            // if crossPoints1 is greater than crossPoint2
            else if (crossPoint1 > crossPoint2)
            {
                // if i is not in (crossPoint2;crossPoint1)
                if (not (i < crossPoint1 and i > crossPoint2))
                    child2[i] = parent1[i];
            }
        }

        // for 0..parent2.size make
        for (int i = 0; i < parent2.size(); i++)
        {
            // if child doesn't have key -> add
            if (std::count(child1.begin(), child1.end(), parent2[i]))
            {
                // for 0..child1.size find free position
                for (int ii = 0; ii < child1.size(); ii++)
                {
                    // free position found -> add
                    if (not child1[ii])
                    {
                        child1[ii] = parent2[i];
                        break;
                    }
                }
            }
        }
    }
    
    //     make mutations
    mutate(child1);
    mutate(child2);

    // push back children to children vector
    children.push_back(child1);
    children.push_back(child2);
    
    parent1.clear();
    parent2.clear();

    child1.clear();
    child2.clear();
}

void Genetic::mutate(vector<int>& child)
{
    // mutation finction
    // if random double if less than mutationFactor
    
    if (mutationMethodVariant == 1)
    {
        //first method
        if (getRandomDouble() < mutationFactor)
        {
            // for 0..swapsInMutation make swaps
            for (int i = 0; i < swapsInMutation; i++)
            {
                swap(child[rand() % dimension],child[rand() % dimension]);
            }
        }
    }
    else if (mutationMethodVariant == 2)
    {
        // second method
        // adjacent swap
        if (getRandomDouble() < mutationFactor)
        {
            for (int i = 0; i < swapsInMutation; i++)
            {
                // get random index from <0;dimension-2> to avoid getting last index or number that not belongs to index set
                int point_ = ((rand() % dimension) - 2);
                int point = point_ < 0 ? 0 : point_;
                
                // make swap of drawn vert with his adjacent
                swap(child[point],child[point+1]);
                // example:
                // 1 2 3 4 5    Drawn: 2
                //after: 1 2 4 3 5
            }
        }
    }
}

void Genetic::generateNewPopulation()
{
    // generating new population
    //vecs inits
    vector<vector<int>> newPopulation;
    newPopulation.reserve(populationSize);
    
    // make asc sort population
    sort(population.begin(), population.end(),
         [this](auto i, auto j)->bool
         {
            return calculateMaxCompletionTime(i) < calculateMaxCompletionTime(j);
         });
    
    // make asc sort on children
    sort(children.begin(), children.end(),
         [this](auto i, auto j)->bool
         {
            return calculateMaxCompletionTime(i) < calculateMaxCompletionTime(j);
         });

    // for 0..populationSize
    for (int i = 0; i < populationSize; i++)
    {
        // if children empty and population not empty
        if (children.empty() and not population.empty())
        {
            newPopulation.push_back(population.back());
            population.pop_back();
            continue;
        }

        // if children not empty and population empty
        if (not children.empty() and population.empty())
        {
            newPopulation.push_back(children.back());
            children.pop_back();
            continue;
        }

        // choose better
        if (population.back() > children.back())
        {
            newPopulation.push_back(population.back());
            population.pop_back();
        }
        else
        {
            newPopulation.push_back(children.back());
            children.pop_back();
        }
    }
    
    // clear vacs
    population.clear();
    children.clear();

    // assign new population
    population = newPopulation;
}
