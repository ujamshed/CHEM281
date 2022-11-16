#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

// Generic print function
void print(std::vector<int> array)
{
    for (int i = 0; i < array.size(); i++)
    {
        if (i == array.size()-1)
        {
            std::cout << array[i] << "";
        }
        else
        {
            std::cout << array[i] << "->";
        }
    }
    std::cout << std::endl;
}

std::map<int, std::vector<int>> job_dependents(std::vector<std::pair<int, int>> job_dependencies)
{
    std::map<int, std::vector<int>> output;

    for (int i = 0; i < job_dependencies.size(); i++)
    {
        // If the job is in the map then add the dependency to the vector of dependencies for that job.
        if (output.find(job_dependencies[i].first) != output.end())
        {
            output[job_dependencies[i].first].push_back(job_dependencies[i].second);
        }
        // If job isnt in the map, then create vector set it equal to the value.
        else
        {
            std::vector<int> job = {job_dependencies[i].second};
            output[job_dependencies[i].first] = job;
        }
    }
    return output;
}

void scheduler(int num_jobs, std::map<int, std::vector<int>> jobs, std::vector<int> schedule)
{
    // Base case: if the number of jobs in the schedule is equal to the number of jobs to do, then we print the current schedule and then return
    if (schedule.size() == num_jobs)
    {
        print(schedule);
        return;
    }

    std::map<int, std::vector<int>> new_jobs;
    
    for (auto const& it: jobs)
    {
        // If the only dependent is the same job, then we can schedule it
        if ((it.second.size() == 1) && (it.first == it.second[0]))
        {
            schedule.push_back(it.first);
        }

        // Check if the job dependents have been completed, if so add it to the schedule.
        else if ((it.second.size() >= 1) && (it.first != it.second[0]))
        {
            bool add = true;
            for (int i = 0; i < it.second.size(); i++)
            {
                // If a single dependent job is not part of the schedule then we cannot add the job to the schedule so we set add to false.
                if(std::find(schedule.begin(), schedule.end(), it.second[i]) == schedule.end())
                {
                    add = false;
                }
            }
            
            // If add is still true, then we schedule the job
            if (add)
            {
                schedule.push_back(it.first);
            }
            else
            {
                // Since we did not add the job to the ready queue, we must add it to the jobs to recurse on the next round.
                new_jobs[it.first] = it.second;
            }
        }
        else
        {
            // Since no statements were fullfilled, this adds the jobs to recurse on the next round
            new_jobs[it.first] = it.second;
        }
    }

    // Recurse until all the jobs are done
    scheduler(num_jobs, new_jobs, schedule);
}

void start(int num_jobs, std::vector<std::pair<int, int>> job_dependencies)
{
    // Ready queue for the schedule
    std::vector<int> schedule;

    // Creates queue for each job that it depends on
    std::map<int, std::vector<int>> jobs = job_dependents(job_dependencies);

    // Runs scheduler
    scheduler(num_jobs, jobs, schedule);
}

int main()
{
    // The integer, num_jobs will always be less than or equal to the job dependencies vector.
    // This is because each job will at a minimum depend on itself.
    
    // Input vector of tuples
    std::vector<std::pair<int, int>> job_dependencies = {{0, 0}, {1, 0}, {2, 3}, {2, 4}, {3, 4}, {4, 1}, {5, 6}, {6, 4}, {7, 6}, {5, 7}};
    
    // Input number of jobs
    int num_jobs = 8;

    // Start
    start(num_jobs, job_dependencies);

    return 0;
}