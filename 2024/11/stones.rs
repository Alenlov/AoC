use std::env;
use std::vec::Vec;
use std::fs::File;
use std::io::prelude::*;
use std::collections::HashMap;

fn split_lines(basic_line: &str) -> Vec<&str> {
    basic_line
        .trim()
        .split("\n")
        .collect()
}

fn create_rules(num : &str) -> Vec<String> {
    if num.len() % 2 == 0 {
        let (mut first, mut second) = num.split_at( num.len()/2 );
        first = first.trim_start_matches('0');
        if first.len() == 0 {first = "0"};
        second = second.trim_start_matches('0');
        if second.len() == 0 {second = "0"};
        return vec![first.to_string(), second.to_string()]
    } else {
        let mut num_val : u64 = num.parse::<u64>().unwrap();
        num_val *= 2024;
        let new_num = num_val.to_string();
        return vec![new_num]
    }
}

fn main() -> std::io::Result<()>{
    let args: Vec<_> = env::args().collect();
    if args.len() <= 1 {
        return Ok(());
    }
    let mut file = File::open(args[1].clone())?;
    let mut contents = String::new();
    file.read_to_string(&mut contents)?;
    let lines : Vec<&str> = split_lines(&contents);

    let init : Vec<&str> = lines[0].split(" ").collect();

    let mut rules : HashMap<String, Vec<String>> = HashMap::from([
        ("0".to_string(), vec!["1".to_string()])
    ]);

    let mut init_stones : HashMap<String, u64> = HashMap::new();

    for n in init {
        init_stones.insert(n.to_string(),1);
    }
    let mut ans_a : u64 = 0;

    let max_blink = 75;
    for b in 0..max_blink{
        if b == 25 {
            ans_a = init_stones.values().sum();
        }
        
        let mut new_stones : HashMap<String, u64> = HashMap::new();
        for (stone, num) in &init_stones {
            rules.entry(stone.to_string()).or_insert(create_rules(stone));
            let stone_rules : Vec<String> = rules[stone].clone();
            for s in stone_rules.iter() {
                new_stones.entry(s.clone()).and_modify(|n| *n += num).or_insert(*num);
            }
        }
        init_stones = new_stones;
    }
    
   
    let ans_b : u64 = init_stones.values().sum();
    
    println!("Answer part A: {}", ans_a);
    println!("Anwer part B: {}", ans_b);
    Ok(())
}
