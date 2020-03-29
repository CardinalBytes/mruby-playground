def get_guess()
    puts "your guess:"
    guess = gets.chomp
    return guess
end

while true do
    n = rand(50)
    puts "guess the number between 0 and 50, type giveup to roll again or quit"
    tries = 0
    while true do
        guess = get_guess()
        if guess == "quit" then 
            puts "Bye"
            abort()
        elsif guess == "giveup" then
            puts "you gave up after #{tries} tries the number was: #{n}"
            break
        end
        guess = guess.to_i
        if guess == n then 
            puts "you won in #{tries} guesses"
            break
        elsif guess < n then
            puts "the number is bigger"
        else
            puts "the number is smaller"
        end
        tries += 1
    end
end
        
    