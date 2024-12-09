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

fn is_correct(changed_pages : &Vec<i64>, rules : &HashMap<i64, HashSet<i64>>) -> bool {
    for i in 1..changed_pages.len() {
        for j in 0..i {
            if rules.get(&changed_pages[i]) != None {
                if rules.get(&changed_pages[i]).expect("Hej2").contains(&changed_pages[j]) {
                    return false;
                }
            }
        }
    }
    return true;
}

fn find_correct(mut changed_pages : Vec<i64>, rules : &HashMap<i64, HashSet<i64>>) -> Vec<i64> {
    let mut correct : bool = false;
    while !correct {
        'outer: for i in 1..changed_pages.len() {
            for j in 0..i {
                if rules.get(&changed_pages[i]) != None {
                    if rules.get(&changed_pages[i]).expect("Hej2").contains(&changed_pages[j]) {
                        //println!("{}, {}, {:?}",j,i,changed_pages);
                        let val = changed_pages.remove(j);
                        let _ = &changed_pages.insert(i, val);
                        //println!("{:?}",changed_pages);
                        
                    }
                }
            }
        }
        correct = is_correct(&changed_pages, rules);
    }
    return changed_pages;
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

    let mut ans_a: i64 = 0;
    let mut ans_b: i64 = 0;

    let mut rules : HashMap<i64, HashSet<i64>> = HashMap::new();
    
    for line in lines {
        if line.find('|') != None {
            let line_split : Vec<&str> = line.split('|').collect();
            let lhs : i64 = line_split[0].parse::<i64>().unwrap();
            let rhs : i64 = line_split[1].parse::<i64>().unwrap();
            if rules.get(&lhs) == None {
                rules.insert(lhs, HashSet::from([rhs]));
            } else {
                rules.get_mut(&lhs).expect("Hej").insert(rhs);
            }
        } else if line.len()>1 {
            let changed_pages : Vec<i64> = line.split(',').map(|c| c.parse::<i64>().unwrap()).collect();
            
            if is_correct(&changed_pages, &rules) {
                //println!("{:?} middle {}",changed_pages,changed_pages[changed_pages.len()/2]);
                ans_a += changed_pages[changed_pages.len()/2];
            } else {
                let fixed_changed_pages = find_correct(changed_pages.clone(), &rules);
                //println!("{:?} middle {}",fixed_changed_pages,fixed_changed_pages[fixed_changed_pages.len()/2]);
                ans_b += fixed_changed_pages[fixed_changed_pages.len()/2];
            }
        }
    }


    println!("Answer part A: {}", ans_a);
    
    println!("Anwer part B: {}", ans_b);
    Ok(())
}
