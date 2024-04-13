Danger Farm Contact Form
========================

This project contains the BCHS implementation of the danger.farm contact form.
Due to the fact that this runs active CGI on a public website, it is a private
project. It is mostly an example of BCHS for future projects.

This project consists of six pieces:
* Contact Form Application Library.
* Contact Form Database Server.
* Contact Form Admin Tool.
* Contact Form Notification Script.
* Contact Form CGI Application.
* Contact Form JS front-end.

Contact Form Application Library
--------------------------------

The Contact Form Application Library contains client/server API methods for
establishing a link to the database server and sending requests / getting
responses. The purpose of this library is to abstract away the socket
serialization and authorization work required for this communication.

Contact Form Database Server
----------------------------

The Contact Form Database Server is a simple C application that is backed using
LMDB. This server can run in application mode or admin mode. Application mode is
restricted to only allowing the "Append Comment" operation. Admin mode allows
connecting clients full access to the database. This split provides an added
layer of defense in depth for this database.

The server first opens and binds a listen socket. Then, it opens the LMDB
database. Once these are established, it uses pledge / unveil to reduce access
to any other system call other than is required to accept new sockets and
perform database operations on the open database descriptor.

The server only serves one connection at a time to simplify concurrency needs.
This is a rather low-volume operation.

For each connection:
* Get the connection type (application / admin) and verify it against
  command-line options.
* For each request, decode and process the request.
  * Append Comment - a stripped comment from the contact form is appended to the
    DB, after it has been stripped of all sus characters.
  * List comments (admin only). A list of comments is returned with the count
    and each comment UUID.
  * Get comment by UUID (admin only). A comment is retrieved by UUID.
  * Delete comment by UUID (admin only). A comment is deleted by UUID.

Contact Form Admin Tool
-----------------------

This is a command-line tool that connects to a server and can run application /
admin commands. It is also the means for integration testing.

Contact Form Notification Script
--------------------------------

This script periodically runs on the server to update a secret page on
danger.farm, indicating the number of contact requests currently waiting for
review.

Contact Form CGI Application
----------------------------

This is a simple KCGI application. It serves CGI requests from the front-end JS
form.

It opens a KCGI socket and a client DB socket. At this point, it pledges to only
do stdio on open descriptors and unveils nothing more on the filesystem.

Forever:
* Get kcgi request.
* Sanity check all values.
* Strip all values of sus characters.
* Send append comment request to the server.
* Send KCGI response.

Contact Form JS Front-End
-------------------------
* ELM based front-end to dynamically send requests and get responses from CGI
  application.
