# Usage tutorial


# Resources
* [Official git documentation](https://git-scm.com/doc)
	* [Official git architectue and usage book](https://git-scm.com/book/en/v2)
* [Official git tutorial](https://git-scm.com/docs/gittutorial)
* [Bitbucket git guide](https://www.atlassian.com/git)


# Information
* [`git clone <repository>` clones nearly all of the repository information that is stored on the server including file change history. Git cloned copy of a repo could even be used to restore nearly all repository information in case of a server crash](https://git-scm.com/book/en/v2/Git-Basics-Getting-a-Git-Repository)
* **It is VERY IMPORTANT to NOT move or copy the `.git` folder from one cloned repo's folder to other's folder when copying files between them or it may lead to some corruption in the repo. You can check if .git was accidentaly copied from one repo to the other by checking if commit history of one repo was copied to the other(as the .git folder contains the commit history of the repository). Also if these repos differ then when .git folder is copied from one to another, most of the files will become(in git status) `"untracked"`(or changed) in the second repo(to where .git folder was copied) as they were not a part of the original repo from where .git folder was copied and so git will view them as some new files in the repo or changes to files that were there(if same files are in both repos) because repo changes(file changes/additions) are tracked using the .git folder.**
* Make sure to use right `mv -r`/`cp -r`:
	* `cp -r folder/* folder2` copies all files and folders from `folder` to `folder2`, but hidden(the ones that start with .) files and folders are not moved/copied
	* `cp -r folder/. folder2` copies all files and folders from `folder` to `folder2`, even the hidden files(the ones that start with .)


# Fixes
## Fixing github's end of password support
* [Creating a token](https://docs.github.com/en/github/authenticating-to-github/keeping-your-account-and-data-secure/creating-a-personal-access-token)
  * Github.com -> Settings -> Developer Settings -> Personal Access Tokens -> Generate Token(No Expiration, Select only "repo" access)
* [Store the credentials so the token does not need to be entered into password propmpt each time](https://stackoverflow.com/a/35943882)
  * Run `git config --global credential.helper store`, then go to some repo and do a push or pull(make sure to do one where account and password is requested) and enter the password, now all of the next times, the password won't be requested(the account and password is stored in - ~/.git-credentials)

## Pull from git while having unpushed commits
* One way to fix is just to do a pull which will merge branches(apply remote changes) and then do a push to push the local changes
*	```
	git pull origin yourBranch           # does a fetch, followed by a merge
	git push origin yourBranch           # push merged branch to remote
	```
