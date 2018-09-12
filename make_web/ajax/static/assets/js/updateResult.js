function ShowResult(RE, max_token, max_token_line, invaild_code){
    var html='';
    html=html+
        `<div>
        <div style="border:none; float: left; width: 20%; padding:15px;">
         <div class="image">

          <img src="static/images/all_img.png" style="width: 130px; height: auto;">
          <div class="text">
            <h3>`+Re["NofCode"]+`</h3>
          </div>
        </div>
        </div>

        <div style="border:none; float: left; width: 20%; padding:15px;">
         <div class="image">

          <img src="static/images/c_img.png" style="width: 130px; height: auto;">
          <div class="text">
            <h3>`+Re["NofC"]+`</h3>
          </div>
        </div>
        </div>

        <div style="border:none; float: left; width: 20%; padding:15px;">
        <div class="image">
          <img src="static/images/cpp_img.png" style="width: 130px; height: auto;">
          <div class="text">
            <h3>`+Re["NofCPP"]+`</h3>
          </div>
        </div>
        </div>

        <div style="border:none; float: left; width: 20%; padding:15px;">
          <div class="image">
          <img src="static/images/java_img.png" style="width: 130px; height: auto;">
          <div class="text">
            <h3>`+Re["NofJAVA"]+`</h3>
          </div>
        </div>
        </div>

        </div>
        <br><br><br><br><br><br><br><br><br>
        <p style="font-size:20px; color:#ffffff; bold; "> MAX Token Code </p>`
        +
        `
        <input class="showcode" type="submit" style="font-size:20px; font-weight: bold;  display:inline-block;  background-color: Transparent; background-repeat:no-repeat; border: none; cursor:pointer; overflow: hidden; outline:none;"   name="show_one_code" id="show_one_code"  value=`+
          max_token + '>' +`<p style="font-size:20px; color:#ffffff; display:inline-block"> - `+max_token_line+` line </p>`

    html=html+`
    <br>
    <br>
    <p style="font-size:20px; color:#ffffff; bold; "> INVAILD CODE </p>`;

    for ( var i in invaild_code ){
      var temp='<input class="showcode" type="submit"  name="show_one_code" id="show_one_code" value='+invaild_code[i]+'>';
      html=html+temp;
    }

    return html;


}
