import smtplib
from email.mime.text import MIMEText
from email.header import Header

class ZMail:
    # connect to the smtp server
    # _mail == smtp server
    # _charset == the mail's charset
    # _subtype == the mail's mimetype's subtype : html, plain
    def __init__(self, smtp_server):
        self._mail = smtplib.SMTP(str(smtp_server))
        self._charset = "utf-8"
        self._subtype = "html"

    def set_charset(self, charset):
        self._charset = charset
    def set_body_testtype(self, subtype):
        self._subtype = subtype

    # sender == the sender's email address
    # receivers == the receivers' email addresses
    # subject == the email's subject 
    # body == the email's body
    def sendmail(self, sender, receivers, subject, body): 
        msg = MIMEText(body, self._subtype, self._charset)
        msg["From"] = sender
        msg["To"] = ";".join(receivers)
        msg["Subject"] = Header(subject, self._charset)
        #print msg.as_string()
        self._mail.sendmail(sender, receivers, msg.as_string())

    # disconnect the smtp server
    def __del__(self):
        self._mail.quit()

# Example
if __name__ == "__main__":
    sender = "heihei@renren-inc.com"
    receivers = ["zhitong.zhang@renren-inc.com"]
    subject = "hello"
    body = "hello, boy"
    m = ZMail("smtp.renren-inc.com")
    m.sendmail(sender, receivers, subject, body)



    
