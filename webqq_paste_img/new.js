window.addEventListener("paste", function(e) {
    items = e.clipboardData.items;
    if (items.length == 0) {
        console.log("No Pasted Data\n");
        return;
    } else {
        console.log("found Pasted Data\n");
    }
    if (window.EQQ != undefined) {
        console.log("found EQQ\n");
    } else {
        console.log("not found EQQ\n");
        return;
    }
    box = EQQ.View.ChatBox.getCurrent();
    file = items[0].getAsFile();
    window.x = file
    if (box && file) {
        uin = EQQ.View.ChatBox.getCurrentUin();
        isGroup = EQQ.View.ChatBox.getCurrent().chatBoxType == "group";
        form = document.getElementById("uploadSendPicfile_" + uin);
        if (isGroup) {
            form.action = EQQ.CONST.UPLOAD_CUSTOM_FACE_SERVER + "?time=" + (new Date).getTime();
        } else {
            form.action = EQQ.CONST.OFFLINE_FILE_SERVER + "upload_offline_pic?time=" + (new Date).getTime();
            form.skey.value = alloy.portal.getUnifiedSkey();
            self = EQQ.Model.BuddyList.getSelf();
            form.uin.value = self.uin;
            receiver = EQQ.Model.BuddyList.getUserByUin(uin);
            //console.log("2");
            form.senderviplevel.value = self.vip || 0;
            form.reciverviplevel.value = receiver.vip || 0;
            //console.log("3");
        }
        //console.log("1");


        fileid = EQQ.View.ChatBox.geneSendPicId();
        form.fileid.value = fileid;
        alloy.portal.recoverCookie();
        //console.log("4");

        form.vfwebqq.value = alloy.portal.getVfWebQQ();
        //console.log("5");
        f = "";
        s_button = document.getElementById("chatBox_sendPicButton_" + uin);
        if (isGroup) {
            f = s_button.removeChild(document.getElementById("custom_face_" + uin));
        } else {
            f = s_button.removeChild(document.getElementById("offline_pic_" + uin));
        }
        //console.log(f);
        formdata = new FormData(form);
        if (isGroup) {
            formdata.append("custom_face", file, "snyh.png");
        } else {
            formdata.append("file", file, "snyh.png");
        }


        iframe = document.getElementById(form.target);
        xhr = new iframe.contentWindow.XMLHttpRequest;
        xhr.open("POST", form.action, true);
        xhr.setRequestHeader("DNT", 1);
        xhr.setRequestHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
        xhr.setRequestHeader("Accept-Language", "en-US,en;q=0.8,zh-CN;q=0.6,zh;q=0.4");

        console.log(form);
        try {
            xhr.onreadystatechange = function (d) {
                if (xhr.readyState == 4) {
                    iframe = document.getElementById(form.target);
                    iframe.contentDocument.write(xhr.response);
                }
                console.log(xhr.response);
            }
            xhr.send(formdata);
            s_button.appendChild(f);
            form.reset();
        } catch (e) {
            console.log(e);
        }

        box.tips("使用截图插件发送中... bug报告:snyh@snyh.org");
        if (isGroup == false) {
            EQQ.View.ChatBox.insertLoading(fileid);
        }
        //console.log("OK");
    }
});
