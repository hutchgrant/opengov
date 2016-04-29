# OpenGov 0.0.1
Search government budget from 2014-2015, with multiple queries, convert all vital data to JSON.

Converts csv columns: ministry, reason for funding, financing 2014-2015.

Calculates the total of all financial data for each query(all ministries combined).

## Table of contents

- [Dependencies](#dependencies)
- [Compile and Run](#compile-and-run)
- [Contributing](#contributing)
- [Creators](#creators)
- [License](#license)

##Dependencies

```bash
# Recommended with Qt5
$ sudo apt-get install qt5-default
```
This was built/tested in Ubuntu 14.04. Debian based distributions should be able to run without issue.  


##Compile and Run
- download and extract opengov.tar.gz 
```
wget https://github.com/hutchgrant/opengov/archive/master.zip
cd ~/Downloads
tar -zxvf opengov*.tar.gz 
```
- Or install git and clone
```
sudo apt-get install git
git clone https://github.com/hutchgrant/opengov.git
```
- Compile
```
cd ./opengov
qmake 
make
```
- Run the compiled binary with
```
./opengov
```
JSON will export by default to the application's path, in a file called "data.json"

You can export JSON to a specific path by adding your path as an argument
```
./opengov /var/www/mysite/data.json
```

You can review the verbose extracted data, in a file called "verbose.txt", within the application's path

##Contributing

see [Contributing](https://github.com/hutchgrant/opengov/blob/master/CONTRIBUTING.md)

## Creator
**Grant Hutchinson**

## License
All code and documentation from 2016 is available under the terms of the [GNU Public License v3](http://www.gnu.org/copyleft/gpl.html)
