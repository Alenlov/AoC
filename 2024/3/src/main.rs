use std::env;
use std::vec::Vec;
use std::fs::File;
use std::io::prelude::*;
use regex::Regex;


fn split_lines(basic_line: &str) -> Vec<&str> {
    basic_line
        .trim()
        .split("\n")
        .collect()
}

fn calc_mul(line: &str) -> i64 {
    let re = Regex::new(r"mul\((\d+),(\d+)\)").unwrap();
    let mut ans : i64 = 0;
    for (_, [lhs, rhs]) in re.captures_iter(line).map(|c| c.extract()) {
        let prod = lhs.parse::<i64>().unwrap() * rhs.parse::<i64>().unwrap();
        println!("{} * {} = {}",lhs,rhs,prod);
        ans += lhs.parse::<i64>().unwrap() * rhs.parse::<i64>().unwrap();
    }
    return ans;
}

fn part_a(lines: &Vec<&str>) -> i64 {
    let mut ans_a : i64 = 0;
    for line in lines {
        ans_a += calc_mul(line);
    }
    return ans_a;
}

fn part_b(lines: &Vec<&str>) -> i64 {
    let mut line = lines.join("");
    let mut ans_b : i64 = 0;
    let mut do_lines : Vec<&str> = line.split("do()").collect();
    for do_line in do_lines {
        println!("{}",do_line);
        let mut do_line_split : Vec<&str> = do_line.split("don't()").collect();
        println!("{}",do_line_split[0]);
        ans_b += calc_mul(do_line_split[0]);
    }
    return ans_b;
}

fn main() -> std::io::Result<()>{
    let args: Vec<_> = env::args().collect();
    if args.len() <= 1 {
        println!("Ingen fil");
        return Ok(());
    }
    let mut file = File::open(args[1].clone())?;
    let mut contents = String::new();
    file.read_to_string(&mut contents)?;
    let lines: Vec<&str> = split_lines(&contents);

    let ans_a : i64 = part_a(&lines);
    let mut ans_b : i64 = part_b(&lines);

        

    println!("Answer part A: {}", ans_a);
    
    println!("Anwer part B: {}", ans_b);
    Ok(())
}
