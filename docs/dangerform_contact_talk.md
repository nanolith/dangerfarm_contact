% Ode to a Contact Form
% Justin Handville
% May 15, 2024

# BCHS and Doing Things the Hard Way

- Let's do some threat modeling for a contact form for a personal website.
- To make things fun, let's engineer it using C and BSD.
- Why not Rust, Go, PHP, Java, Python, Ruby, etc.?
  - We will encounter C specific vulns.
  - Not all vulns are specific to C, and some exist in each alt language.
  - We can anticipate, mitigate, and in some places, prevent most of these.
- This is the "hard way", but that's applicable to firmware and OS.

# Threat Modeling

- Contact forms are an injection point for spam and potential exploits.
- Think you're safe with language / platform X?
  - Vulnerabilities in Unicode exist up and down the stack.
  - A 24-year-old RCE vuln was just found in April in libc's iconv, exploitable
    with PHP.
- Attackers have something to gain. Not as exciting as a bank or tech company.
  - Website defacement or malware / scam serving.
  - Gaining access to e-mail accounts and potential second factors.
  - Access to the instance for running crypto mining or launching VM attacks.
  - Adding to a botnet.

# Defense in Depth

- We can split the services into a CGI script and a database with capabilities
  lockdown at the application layer.
- Reading messages can be done safely with a locked down terminal application,
  IF we get string handling right.
- Between these applications, we can enforce a simple binary protocol that
  limits the potential for exploits.
- We can use formal methods to verify that the binary protocol is safer.
- We can use formal methods to verify that UTF-8 string handling is safer.
- We can lock down these services with runtime mitigations.
  - pledge / unveil on OpenBSD
  - capsicum on FreeBSD
  - stretch goal: seccomp on Linux

# Application Decomposition Diagram

# String Handling

# Model Checking the String Handler

# Binary Protocol

# Model Checking the Binary Protocol

# Database Server

# Database Server Threats

# Model Checking the Database Server

# Using pledge / unveil to Lock Down the Database

# Using capsicum to Lock Down the Database

# CGI Application

# CGI Application Threats

# Model Checking the CGI Application

# Using pledge / unveil to Lock Down the CGI Application

# Using capsicum to Lock Down the CGI Application

# Admin Tool

# Admin Tool Threats

# Model Checking the Admin Tool

# Using pledge / unveil to Lock Down the Admin Tool

# Using capsicum to Lock Down the Admin Tool
