<script>
  window.fbAsyncInit = function() {
    FB.init({
      appId      : '437375113121578',
      xfbml      : true,
      version    : 'v2.5'
    });
      console.log("success!");
  };

  (function(d, s, id){
     var js, fjs = d.getElementsByTagName(s)[0];
     if (d.getElementById(id)) {return;}
     js = d.createElement(s); js.id = id;
     js.src = "//connect.facebook.net/en_US/sdk.js";
     fjs.parentNode.insertBefore(js, fjs);
    console.log("success again!!"); 
  }(document, 'script', 'facebook-jssdk'));
</script>

<script>
// Only works after `FB.init` is called
function myFacebookLogin() {
  FB.login(function(){
      
    FB.api(
    "/547980662/friends/1776592672",
    function (response) {
      if (response && !response.error) {
        /* handle the result */
          console.log(response);
      }
        else
            {console.log("No response");}
    }
);  
      
      
  }, {scope: 'publish_actions'});;
}
</script>
<button onclick="myFacebookLogin()">Login with Facebook</button></li>
    
    </ol>
