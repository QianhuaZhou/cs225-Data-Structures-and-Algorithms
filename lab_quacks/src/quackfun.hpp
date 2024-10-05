/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 * stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 *
 * **Hint**: think recursively!
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the Standard Template Library (STL) stack in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param s A stack holding values to sum.
 * @return  The sum of all the elements in the stack, leaving the original
 *          stack in the same state (unchanged).
 */
template <typename T>
T sum(stack<T>& s)
{
    // Your code here
    if(s.empty()) return T();
    T topEle = s.top();
    T sum_;
    s.pop();//no return velue!!!
    //sum_ = sum_ + sum(s);
    T prev_sum = sum(s);
    s.push(topEle);
    return topEle + prev_sum; // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of parentheses, curly/square brackets and other
 * characters. This function will return true if and only if the bracket
 * characters in the given string are balanced. For this to be true, all
 * brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello=](){}" is balanced, "{()[{a}]}" is
 * balanced, "[})" is unbalanced, "][" is unbalanced, and "))))[cs225]" is
 * unbalanced.
 *
 * For this function, you may only create a single local variable of type
 * `stack<char>`! No other stack or queue local objects may be declared. Note
 * that you may still declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return      Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)//need rewrite
{
    // @TODO: Make less optimistic
    stack<char> s;
    //char first = input.back();
    //while(input.back() != ' '){//gain the most right element without removing it
    while(!input.empty()){
        char q_front = input.front();
        if(q_front == '[' || q_front == '(' ||q_front == '{'){
            s.push(q_front);
        }else if(q_front == ']' || q_front == ')' ||q_front == '}'){
            if(s.empty()) return false;
            char s_top = s.top();
            s.pop();
           if ((q_front == ']' && s_top != '[') ||
                (q_front == ')' && s_top != '(') ||
                (q_front == '}' && s_top != '{')) {
                return false;
            }
        }
        //input.dequeue(); ????
        input.pop();
    }
    if(!s.empty()) return false;
    return true;
    

}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 *
 * **Hint**: You'll want to make a local stack variable.
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the Standard Template Library (STL) queue in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param q A queue of items to be scrambled
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    queue<T> q2;
    int levelCount = 1; 
    while (!q.empty()) {
        int elementsInLevel = std::min(levelCount, static_cast<int>(q.size()));
        if (levelCount % 2 == 0) {//even
            for (int i = 0; i < elementsInLevel; ++i) {
                s.push(q.front());
                q.pop();
            }
            while (!s.empty()) {
                q2.push(s.top());
                s.pop();
            }
        } else {//odd
            for (int i = 0; i < elementsInLevel; ++i) {
                q2.push(q.front());
                q.pop();
            }
        }
        levelCount++;
    }
    q = q2;
}
}