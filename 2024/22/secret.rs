use std::env;
use std::vec::Vec;
use std::fs::File;
use std::io::prelude::*;
use std::collections::HashMap;
use std::collections::HashSet;

fn split_lines(basic_line: &str) -> Vec<&str> {
    basic_line
        .trim()
        .split("\n")
        .collect()
}

fn update_secret(mut cur: u64) -> u64 {
    let mut new: u64 = cur*64;
    new = mix(new, cur);
    cur = prune(new);
    
    new = cur / 32;
    new = mix(new, cur);
    cur = prune(new);

    new = cur * 2048;
    new = mix(new, cur);
    new = prune(new);

    return new
}

fn mix(new: u64, cur: u64) -> u64 {
    return new ^ cur
}

fn prune(new: u64) -> u64 {
    return new % 16777216
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
    
    let mut ans_a: u64 = 0;
    let mut ans_b: u64 = 0;
    
    let mut bananas: HashMap<Vec<i32>,u64> = HashMap::new();

    

    for line in lines {
        let mut diff_set: HashSet<Vec<i32>> = HashSet::new();
        let mut diff_vec = vec![0;2000];
        let mut sec = line.parse::<u64>().unwrap();
        let mut cost = sec%10;
        for i in 0..2000 {
            sec = update_secret(sec);
            diff_vec[i] = ((sec%10) as i32) - (cost as i32);
            cost = sec%10;
            if i >= 3 {
                let cur_vec = diff_vec[(i-3)..=i].to_vec();
                if !diff_set.contains(&cur_vec) {
                    diff_set.insert(cur_vec.clone());
                    
                    bananas.entry(cur_vec.clone()).and_modify(|c| *c += cost).or_insert(cost);
                    
                }
                //println!("{:?} - {}",cur_vec, cost);
                //println!("{:?}", cur_vec);
            }
        }
        ans_a += sec;
        // println!("{}: {}",line, sec);
    }

    println!("Answer part A: {}", ans_a);

    

    for (k, v) in &bananas {
        if *v > ans_b {
            ans_b = *v;
            //println!("{:?} - {}", k, v);
        }
    }

    println!("Answer part B: {}", ans_b);

    //println!("Num steps tot: {:?}",*route.get(&end_pos).unwrap());

    
    Ok(())
}
